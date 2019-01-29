////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server config upload control panel
//
////////////////////////////////////////////////////////////////////////////////

namespace SFServerManager
{
    partial class ServerConfigUploadControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listXMLFile = new System.Windows.Forms.ComboBox();
            this.textServerIP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnXMLBrowse = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textCommandNodePath = new System.Windows.Forms.TextBox();
            this.textConfigNodePath = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textModulePath = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // listXMLFile
            // 
            this.listXMLFile.FormattingEnabled = true;
            this.listXMLFile.Location = new System.Drawing.Point(96, 25);
            this.listXMLFile.Name = "listXMLFile";
            this.listXMLFile.Size = new System.Drawing.Size(548, 21);
            this.listXMLFile.TabIndex = 0;
            this.listXMLFile.SelectedIndexChanged += new System.EventHandler(this.OnXMLSelectionChanged);
            this.listXMLFile.Leave += new System.EventHandler(this.OnXMLEditLeave);
            // 
            // textServerIP
            // 
            this.textServerIP.Location = new System.Drawing.Point(96, 61);
            this.textServerIP.Name = "textServerIP";
            this.textServerIP.Size = new System.Drawing.Size(548, 20);
            this.textServerIP.TabIndex = 2;
            this.textServerIP.Leave += new System.EventHandler(this.OnServerIPEditLeave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "XMLFile";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "ServerIP";
            // 
            // btnXMLBrowse
            // 
            this.btnXMLBrowse.Location = new System.Drawing.Point(650, 25);
            this.btnXMLBrowse.Name = "btnXMLBrowse";
            this.btnXMLBrowse.Size = new System.Drawing.Size(23, 23);
            this.btnXMLBrowse.TabIndex = 8;
            this.btnXMLBrowse.Text = "..";
            this.btnXMLBrowse.UseVisualStyleBackColor = true;
            this.btnXMLBrowse.Click += new System.EventHandler(this.OnXMLBrowse);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 127);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(76, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "CommandPath";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 99);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "ConfigPath";
            // 
            // textCommandNodePath
            // 
            this.textCommandNodePath.Enabled = false;
            this.textCommandNodePath.Location = new System.Drawing.Point(96, 124);
            this.textCommandNodePath.Name = "textCommandNodePath";
            this.textCommandNodePath.Size = new System.Drawing.Size(548, 20);
            this.textCommandNodePath.TabIndex = 6;
            this.textCommandNodePath.TextChanged += new System.EventHandler(this.OnCommandPathChanged);
            // 
            // textConfigNodePath
            // 
            this.textConfigNodePath.Enabled = false;
            this.textConfigNodePath.Location = new System.Drawing.Point(96, 92);
            this.textConfigNodePath.Name = "textConfigNodePath";
            this.textConfigNodePath.Size = new System.Drawing.Size(548, 20);
            this.textConfigNodePath.TabIndex = 1;
            this.textConfigNodePath.TextChanged += new System.EventHandler(this.OnConfigPathChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 155);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(64, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "ModulePath";
            // 
            // textModulePath
            // 
            this.textModulePath.Location = new System.Drawing.Point(97, 152);
            this.textModulePath.Name = "textModulePath";
            this.textModulePath.Size = new System.Drawing.Size(548, 20);
            this.textModulePath.TabIndex = 9;
            this.textModulePath.TextChanged += new System.EventHandler(this.OnMoudlePathChanged);
            // 
            // ServerConfigUploadControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textModulePath);
            this.Controls.Add(this.btnXMLBrowse);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textCommandNodePath);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textServerIP);
            this.Controls.Add(this.textConfigNodePath);
            this.Controls.Add(this.listXMLFile);
            this.Name = "ServerConfigUploadControl";
            this.Size = new System.Drawing.Size(689, 221);
            this.Load += new System.EventHandler(this.OnLoaded);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox listXMLFile;
        private System.Windows.Forms.TextBox textServerIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnXMLBrowse;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textCommandNodePath;
        private System.Windows.Forms.TextBox textConfigNodePath;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textModulePath;
    }
}
