////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tong compiler main
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Dom;

//using SF;


namespace SFConvertVSProj2CMake
{
    class Program
    {
        /// <summary>
        /// The main entry point for the application</summary>
        [STAThread]
        static void Main()
        {
            // It's important to call these before starting the app; otherwise theming and bitmaps
            //  may not render correctly.
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.DoEvents(); // see http://www.codeproject.com/buglist/EnableVisualStylesBug.asp?df=100&forumid=25268&exp=0&select=984714

            //Engine engine = new Engine();
            //engine.StartEngine();

            // Set up localization support early on, so that user-readable strings will be localized
            //  during the initialization phase below. Use XML files that are embedded resources.
            Thread.CurrentThread.CurrentUICulture = System.Globalization.CultureInfo.CurrentCulture;
            Localizer.SetStringLocalizer(new EmbeddedResourceStringLocalizer());

            // Enable metadata driven property editing for the DOM
            DomNodeType.BaseOfAllTypes.AddAdapterCreator(new AdapterCreator<CustomTypeDescriptorNodeAdapter>());

            // Create a type catalog with the types of components we want in the application
            var catalog = new TypeCatalog(

                typeof(SettingsService),                // persistent settings and user preferences dialog
                                                        //typeof(StatusService),                  // status bar at bottom of main Form
                typeof(UnhandledExceptionService),      // catches unhandled exceptions, displays info, and gives user a chance to save
                typeof(FileDialogService),              // standard Windows file dialogs

                typeof(DomNodeRefDictionary),           // Reference dictionary
                //typeof(TongScriptCompilerTypeManager),
                //typeof(ScriptNodeDefinitionManager),
                //typeof(ZooKeeperSession),
                //typeof(TongCompilerStart),
                //typeof(TongCompilerBatchRead),
                //typeof(TongCompilerBatchGenerateBytecode),

                typeof(Outputs),                        // passes messages to all log writers
                typeof(ErrorDialogService),             // displays errors to the user in a message box
                typeof(ConsoleOutputWriter)

            );

            // Set up the MEF container with these components
            var container = new CompositionContainer(catalog);

            // Configure the main Form
            var batch = new CompositionBatch();
            var mainForm = new ConsoleMainForm()
            {
                Text = Application.ProductName,
            };

            // Add the main Form instance, etc., to the container
            batch.AddPart(mainForm);
            container.Compose(batch);

            container.InitializeAll();

            mainForm.Run();
            mainForm.Close();

            // Give components a chance to clean up.
            container.Dispose();

            //engine.StopEngine();
        }

    }
}
