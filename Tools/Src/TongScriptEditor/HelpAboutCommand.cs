////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Help about command
//
////////////////////////////////////////////////////////////////////////////////


using System.ComponentModel.Composition;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using Sce.Atf;
using Sce.Atf.Controls;

namespace SF.Tong.Editor
{
    /// <summary>
    /// Adds the Help/About command, which displays a dialog box with a description
    /// of the application (specified by a derived class) plus the ATF version number</summary>
    [Export(typeof(IInitializable))]
    [Export(typeof(HelpAboutCommand))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class HelpAboutCommand : Sce.Atf.Applications.HelpAboutCommand
    {
        /// <summary>
        /// Shows the About dialog box</summary>
        /// <remarks>Derived classes should copy this method and customize it.
        /// It is recommended to display the ATF version number to aid in diagnosing
        /// problems. (Pass in 'true' to AboutDialog's constructor or use AtfVersion.)</remarks>
        protected override void ShowHelpAbout()
        {
            var richTextBox = new RichTextBox();
            richTextBox.BorderStyle = BorderStyle.None;
            richTextBox.ReadOnly = true;

            string languageCode = CultureInfo.CurrentCulture.TwoLetterISOLanguageName;
            string aboutFilePath;
            if (languageCode == "ja")
                aboutFilePath = "SF.Tong.Editor.Resources.ja.About.rtf";
            else
                aboutFilePath = "SF.Tong.Editor.Resources.About.rtf";
            
            Stream textFileStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(aboutFilePath);
            if (textFileStream != null)
                richTextBox.LoadFile(textFileStream, RichTextBoxStreamType.RichText);

            const string appUrl = "https://github.com/SonyWWS/ATF/wiki";
            var dialog = new AboutDialog(
                "Visual script Editor Sample".Localize(), appUrl, richTextBox, null, null, true);
            dialog.ShowDialog();
        }
    }
}
