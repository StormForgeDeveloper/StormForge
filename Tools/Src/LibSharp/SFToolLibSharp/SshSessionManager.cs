using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using SF;
using SF.Tool;
using Renci.SshNet;
using System.Text.RegularExpressions;

namespace SF
{
    public class SSHSession
    {
        SshClient m_sshClient;
        string m_Password; // password for sudo commands

        IEnumerable<ForwardedPort> ForwardedPorts => m_sshClient.ForwardedPorts;


        public SSHSession(string sshHostName, string sshUserName, string sshPassword = null,
            string sshKeyFile = null, string sshPassPhrase = null, int sshPort = 22)
        {
            var sshClient = ConnectSsh(sshHostName,
                    sshUserName, 
                    sshPassword: sshPassword,
                    sshKeyFile: sshKeyFile, sshPassPhrase: sshPassPhrase,
                    sshPort: sshPort);

            m_sshClient = sshClient;
            m_Password = sshPassword;
        }

        public static SshClient ConnectSsh(
            string sshHostName, string sshUserName, string sshPassword = null,
            string sshKeyFile = null, string sshPassPhrase = null, int sshPort = 22)
        {
            // check arguments
            if (string.IsNullOrEmpty(sshHostName))
                throw new ArgumentException($"{nameof(sshHostName)} must be specified.", nameof(sshHostName));
            if (string.IsNullOrEmpty(sshHostName))
                throw new ArgumentException($"{nameof(sshUserName)} must be specified.", nameof(sshUserName));
            if (string.IsNullOrEmpty(sshPassword) && string.IsNullOrEmpty(sshKeyFile))
                throw new ArgumentException($"One of {nameof(sshPassword)} and {nameof(sshKeyFile)} must be specified.");

            // define the authentication methods to use (in order)
            var authenticationMethods = new List<AuthenticationMethod>();
            if (!string.IsNullOrEmpty(sshKeyFile))
            {
                authenticationMethods.Add(new PrivateKeyAuthenticationMethod(sshUserName,
                    new PrivateKeyFile(sshKeyFile, string.IsNullOrEmpty(sshPassPhrase) ? null : sshPassPhrase)));
            }
            if (!string.IsNullOrEmpty(sshPassword))
            {
                authenticationMethods.Add(new PasswordAuthenticationMethod(sshUserName, sshPassword));
            }

            // connect to the SSH server
            var sshClient = new SshClient(new ConnectionInfo(sshHostName, sshPort, sshUserName, authenticationMethods.ToArray()));
            sshClient.Connect();

            return sshClient;
        }


        // Add ssh tunneling port. returns forwarded local port
        public uint AddPortForward(string host, uint port)
        {
            if (m_sshClient == null)
                return 0;

            var forwardedPort = new ForwardedPortLocal("127.0.0.1", host, port);
            m_sshClient.AddForwardedPort(forwardedPort);
            forwardedPort.Start();

            return forwardedPort.BoundPort;
        }


        TimeSpan m_WaitTime = new TimeSpan(0, 0, 2);

        void FlushCommandResultLines(ShellStream stream)
        {
            string resultString = null;
            int timeOut = 120;
            var LastReactTime = DateTime.Now;

            while ((DateTime.Now - LastReactTime).TotalSeconds < timeOut)
            {
                if (resultString != null)
                {
                    timeOut = 10;
                    LastReactTime = DateTime.Now;

                    if (resultString.IndexOf(m_Password) < 0)
                    {
                        SF.Log.Info("{0}", resultString);
                        System.Diagnostics.Debug.Print(resultString);
                    }

                    if (resultString.IndexOf("[sudo] password for ") >= 0)
                    {
                        stream.WriteLine(m_Password);
                    }
                    else if (resultString.TrimEnd().EndsWith('$'))
                    {
                        timeOut = 1; // bash prompt
                    }
                }

                resultString = stream.ReadLine(m_WaitTime);
            }

            if (!string.IsNullOrEmpty(resultString) && (resultString.IndexOf(m_Password) < 0))
                SF.Log.Info("{0}", resultString);

        }

        public Task RunBatchCommands(string[] commands)
        {
            SF.Log.Info("Running remote commands: {0}", commands.Length);

            var modes = new Dictionary<Renci.SshNet.Common.TerminalModes, uint>();

            var task = new Task(() =>
            {
                using (var stream = m_sshClient.CreateShellStream("xterm", 255, 50, 800, 600, 1024, modes))
                {
                    stream.WriteLine("sudo pwd"); // Forcing sudo password trigger so that it doesn't ask later
                    FlushCommandResultLines(stream);

                    foreach (var command in commands)
                    {
                        stream.WriteLine(command+"\r"); // Adding \r forcing them to print prompt when action is finished
                        FlushCommandResultLines(stream);
                    }
                }

                SF.Log.Info("Finished remote commands");
            });

            task.Start();

            return task;
        }
    }


    public static class SSHSessionManager
    {
        static public string DefaultSession = "default";

        static Dictionary<string, SSHSession> m_SessionMap = new Dictionary<string, SSHSession>();


        static SSHSessionManager()
        {
            CreateSession("default", AppConfig.GetValue<string>("SSHServer"),
                    AppConfig.GetValue<string>("SSHUser"),
                    sshPassword: AppConfig.GetValue<string>("SSHPassword"),
                    sshPort: AppConfig.GetValue<int>("SSHPort"));
        }

        public static SSHSession GetSession(string sessionName)
        {
            SSHSession session;
            if (!m_SessionMap.TryGetValue(sessionName, out session))
            {
                m_SessionMap.TryGetValue("default", out session);
            }

            return session;
        }
        public static SSHSession CreateSession(string sessionName, string sshHostName, string sshUserName, 
            string sshPassword = null,
            string sshKeyFile = null, string sshPassPhrase = null, 
            int sshPort = 22)
        {
            SSHSession session;
            if (m_SessionMap.TryGetValue(sessionName, out session))
                return session;

            session = new SSHSession(sshHostName,
                    sshUserName,
                    sshPassword: sshPassword,
                    sshKeyFile: sshKeyFile, sshPassPhrase: sshPassPhrase,
                    sshPort: sshPort);

            m_SessionMap.Add(sessionName, session);

            return session;
        }
    }
}
