using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SF;
using SF.Tool;
using MySql.Data.MySqlClient;
using MySqlX.XDevAPI;
using Renci.SshNet;

namespace SF
{
    public class SSHSessionmanager
    {
        SshClient m_sshClient;
        List<ForwardedPortLocal> m_PortForwards = new List<ForwardedPortLocal>();

        public SSHSessionmanager()
        {
            InitializeSSH();
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

        void InitializeSSH()
        {
            try
            {
                var sshClient = ConnectSsh(AppConfig.GetValue<string>("SSHServer"),
                    AppConfig.GetValue<string>("SSHUser"), AppConfig.GetValue<string>("SSHPassword"),
                    sshPort: AppConfig.GetValue<int>("SSHPort"));

                m_sshClient = sshClient;
            }
            catch (Exception exp)
            {
                SF.Log.Error("{0} => {1}", exp.Message, exp.StackTrace.ToString());
            }

        }

        // Add ssh tunneling port. returns forwarded local port
        public uint AddPortForward(string host, uint port)
        {
            if (m_sshClient == null)
                return 0;

            m_PortForwards
        }
    }
}
