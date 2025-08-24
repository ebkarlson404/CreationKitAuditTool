# Overview
The Creation Kit Audit Tool is an adjunct tool that one can run in conjunection with the [Starfield Creation Kit](https://store.steampowered.com/app/2722710/Starfield_Creation_Kit/) to automate the process of reliably creating ACHLIST packing lists for one's plugins.  This tool solves
three of the most problematic aspects of Starfield's Creation Kit design/implementation:
1. Reliably detects all files that have been changed within one's Starfield Installation Tree
2. Automatically handles replicating files from the *MyMod.ESP* directories created by Creation Kit into corresponding *MyMod.ESM* directories for distribution with one's ESM-based plugin.
3. Works with a suitably configured WWise deployment to create platform-specific ACHLIST packing lists in a single pass.
## Reliable File Detection
One known issue with Starfield's Creation Kit is that the *Archive* tool does not reliably detect all the files that have been added/altered as part
of a given plugin.  The Creation Kit Audit Tool solves this problem by using the native Windows API's to watch for any file changes
within one's Starfield Installation Tree.  The tool will maintain an audit log of all files added/altered during its run and use
that audit log to generate suitable ACHLIST packing lists for the Creation Kit.
## ESP to ESM Replication
One unfortunate design decision in Starfield and its Creation Kit is the directory naming scheme used for some files associated with
a given plugin.  The naming scheme is to place some plugin-specific files in a directory whose name matches the name of the plugin file.
Unforunately, the naming scheme *includes* the extension for the plugin file.  The issue this creates is that since Creation Kit
works on plugin files whose names end with `.ESP`, it places the plugin-specific files in a directory named *MyMod.ESP*.  However,
when the plugin is published Creation Kit creates a plugin file with an extension of `.ESM` so when Starfield loads the `.ESM` plugin
file, it will look for the plugin-specific files in a directory named *MyMod.ESM*, which does not exist.

The Creation Kit Audit Tool will automatically detect when plugin files reside in a *MyMod.ESP* directory and will replicate those
files into a corresponding *MyMod.ESM* directory to use for the generated ACHLIST packing list.  This will result in a
`BA2` file that is ready to ship with the resulting `.ESM` plugin file.
## WWise Configuration: Streamlined Multi-Platform Distribution
For some reason, the format of the audio WEM files is platform-specific.  So WEM files meant for a PC platform cannot be used on
an XBox and vice versa.  This makes generation of cross-platform plugins tedious as the nominal configuration for the WWise
audio toolkit that integrates into the Starfield Creation Kit is specific to one platform or the other.  This forces one to
do all the work to create the PC version of one's plugin, pack the `BA2` archive files, then exit Creation Kit, change the
`CreationKitCustom.ini` file to reconfigure WWise to generate XBox WEM files, restart Creation Kit, regenerate the WEM files
and then pack the XBox-specific `BA2` archive files.

The Creation Kit Audit Tool has been engineered to work with an alternate WWise configuration which will generate *both*
the PC and XBox WEM files in a single pass, placing the XBox WEM files into an alternate directory tree.  The Creation Kit
Audit Tool can be configured to know about this alternate XBox WEM tree and generate the two platform-specific ACHLIST
packing lists that will pull the WEM files from the appropriate tree for each platform.

To configure the Starfield Creation Kit for single-pass WEM generation, go into your `CreationKitCustom.ini` file and
ensure that the `Audio` settings are as follows:
> [Audio]  
> bProcessAudioForPC=1  
> bProcessAudioForXB=1  
> sPathToVoiceOutputPC=  
> sPathToVoiceOutputXB=XBOX\Data\Sound\Voice  
> sPathToSoundBankOutputPC=  
> sPathToSoundBankOutputXB=XBOX\Data\Sound\SoundBanks  
> bLogWwiseConversationOutput=1  
> sPathToWwiseProj=Tools\wwise\Starfield\Starfield.wproj  

Then go to your Starfield Installation Folder and create a folder named `XBOX` and then within that folder a subfolder named `Data`.

When one runs the Creation Kit Audit Tool, ensure that the XBox WEM Folder is set to the `XBOX` folder that you created inside your Starfield Installtion Folder.

Now when one uses the `Audio | Process Local Voice WAVs` or `Audio | Build Soundbank for Active File` tool in Creation
Kit to process `.WAV` files into `.WEM` files, it will create *both* the PC and XBox WEM files in a single pass, placing the XBox WEM
files into the alternate directory paths specified in the `CreationKitCustom.ini` file above.  The Creation Kit Audit Tool
will detect both files and add them to the audit log for the plugin.  When one uses the Creation Kit Audit Tool to generate
the ACHLIST packing lists for the plugin, it will create two such lists - one for the PC platform that packs the PC WEM
files, and one for the XBox platform that packs the XBox WEM files.  One can pull these ACHLIST files into Creation Kit
to generate the two, platform-specific, `BA2` archive files to distributed your plugin to both platforms.

# Quick Start Instructions
1. Ensure that you have a properly deployed Starfield Creation Kit
2. If you will be generating WEM files as part of your plugin work, ensure that you have setup the `Audio` configuration block as detailed above
3. Start up the Creation Kit and load up your plugin
4. Start up the Creation Kit Audit Tool and configure the `Starfield Installation Folder` (which is where your *starfield.exe* executable was installed, and the `XBOX WEM Folder` (which would be the `XBOX` folder under your starfield installation folder if you follow the instructions above for configuring the `[Audio]` settings in your *CreationKitCustom.ini* file.  Note that if you have configured these two items before, the previous setings will be auto-configured for you.
5. Tell Creation Kit Audit Tool which plugin you are working on.  If you have worked on this plugin with the Creation Kit Audit Tool before, the audit log for the plugin will be initialized from the previous run.  If this is the first time that you're using the Creation Kit Audit Tool for this plugin, you can load your old ACHLIST file via the `Import` button to initialize the set of files to include.
6. Click `Start` in the Creation Kit Audit Tool
7. Go back to your Creation Kit and work on your plugin
8. When you are ready to package the plugin, go back to the Creation Kit Audit Tool and click on the `Generate` button to create the two platform-specific ACHLIST files.  They will be created in your `%USERPROFILE%\Documents\My Games\Starfield\CreationKitAuditTool` directory.
9. Go back to Creation Kit and use the `Archive` tool to pack your `BA2` files by importing the ACHLIST files that were stored in your `%USERPROFILE%\Documents\My Games\Starfield\CreationKitAuditTool` directory.

# Tips, Tricks and Notes
## Audit Processing
You can suspend the audit processing at any time by clicking on the `Stop` button in the Creation Kit Audit Tool and then resume audit
processing by clicking on `Start` again.  Note that clicking on the red or green `Status` button will toggle the audit processing.

Altered/Created files are only detected while the audit process is running.  Suspending the audit process allows one to make changes
inside the Starfield Installation tree without having those changes picked up by the Creation Kit Audit Tool.  Resuming the audit
process will append newly discovered files to the existing audit log.

## Manually Altering the Audit Log
If one should decide that the audit log for a given plugin has missed some files that it should have, or captured some files
that it should not have, one can manually alter the audit log.

To add missing files to the audit log, use the `+` button to the right of the audit log list.  This will bring up a file-picker
dialog which will allow one to select additional files to add to the audit log.  Note that one can select multiple files at
once as long as they are all in the same folder.  Note that there is a filtering control in the lower right corner of the
file-picker that will allow one to restrict the set of files displayed, or use the `All (*.*)` choice to see all files.

To remove a captured file from the audit log, right click on the errant file and then click on the `Remove From Audit`
menu item.  Note that a removed item can be rediscovered if it is modified later on while the audit tool is running.

One can also completely clear the audit log by clicking on the `Clear` button in the `Audit Control` group at the bottom of
the window. This will pop up a confirmation window to remove all files from the audit log.

## Importing existing ACHLIST files
If you have a plugin that was created prior to using the Creation Kit Audit Tool, one can import the contents of
one's old ACHLIST file into the plugin's audit log.  Use the `Import` button in the `Audit Control` group at the bottom
of the window.  This will pop up a file-picker dialog that will allow one to choose an existing ACHLIST file for importing.

## Customized Audit Filtering
Not all files that are altered/created in the Starfield Installation tree should be distributed with one's plugin.  The
Creation Kit Audit Tool comes pre-configured with a set of filters to ignore irrelevant files by extension.  One
can customize this list of filters by clicking on `File | Audit Filters`.  This will bring up a dialog that allows one
to add/remove file extensions from the filtering logic.  Note that any changes made here will be saved in a
`%USERPROFILE%\Documents\My Games\Starfield\CreationKitAuditTool\CustomFilters.txt` file and will be automatically
loaded everytime that one starts the Creation Kit Audit Tool.

## Plugin Manifest Files
Once the Creation Kit Audit Tool has been used for a given plugin, it will save the manifest of all files detected during the audit
session in a file named *MyMod.manifest* in your `%USERPROFILE%\Documents\My Games\Starfield\CreationKitAuditTool` directory. This
manifest file is nothing more than a list of all the discovered files with one file per line.  One can create/edit a manifest file
directly by hand if one wants to manually setup the initial audit log for a plugin.  Note that editing a manifest file for a given
plugin while the Creation Kit Audit Tool is running an audit on that plugin will almost certainly result in the tool overwriting
any manual changes made to the file.

Once the manifest file has been created for a given plugin, the Creation Kit Audit Tool will use this manifest file to reload the
audit log for that plugin the next time that the audit tool is used to monitor activity for that plugin.

## Autodiscovery of New Plugins
The Creation Kit Audit Tool can be configured to capture altered/created files while waiting for one to create
a new plugin in the Creation Kit.  To do so, choose the `<autodetect>` option in the `Plugin Name` dropdown and
then click on the `Start` button to start the audit process.  The Creation Kit Audit Tool will capture files
that are created in the Starfield Installation tree while it waits for a new *MyMod.ESP* file to show up in
the Starfield Data folder.  When one creates the new *MyMod.ESP* file via Creation Kit, the Creation Kit Audit Tool
will automatically add the new plugin to its list of registered plugins and initialize its manifest with the
files that have been captured so far.

## Continuous Replication
Normally files are not replicated from *ESP* directories to *ESM* directories until one clicks on the `Generate`
button to regenerate the ACHLIST files.  This means that the contents of the *ESM* directories can become stale
with respect to their *ESP* counterpoints.  Continuous Replication will perform this replication immediately with
every file-change notification that is received by the audit tool, thereby keeping the *ESM* directories
synchronized to their corresponding *ESP* directories in real time.  This can be useful if one has some other
tool or process that requires fully synchronized *ESM* directories.

Note that the *ESP* to *ESM* replication will still happen when one clicks on the `Generate` button irrespective
of whether one has enabled the Continuous Replication feature.

Note that Continuous Replication only takes place while the audit process is running.  If one pauses the audit
process, Continuous Replication will also be paused until the audit process is resumed.

## %USERPROFILE%\Documents\My Games\Starfield\CreationKitAuditTool
This folder is created by the Creation Kit Audit Tool and is used to store persistent data used or generated
by the tool:

- *.manifest: These are the manifest files for all plugins known to the audit tool
- *.achlist: These are the ACHLIST packing files generated by the audit tool
- CustomFilters.txt: This holds the customized list of audit filters

# Runtime Requirements
The Creation Kit Audit Tool will run on Windows 10 or 11 using the .NET runtime version 4.7.2 or later.

# Build Configuration
One can download the project files from GitHub and build the tool locally if one so desires.  In order to do so
one must first prepare their build environment as follows:
1. Download and install [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)
2. Go into `Tools | Get Tools and Features ...` and ensure that you have the `Desktop development with C++` feature installed with the `C++/CLI support for v143 build tools` package included.  See this third-party video for a walk-through: [Create your first C++ GUI WIndows Form using Visual Studio 2022](https://youtu.be/AINCOpXma6M?t=90)
3. Go into `Git | Clone repository` to pull down the repo from GitHub: `https://github.com/ebkarlson404/CreationKitAuditTool.git`.

Note that GitHub has a choice in the `<> Code` drop down for `Open with Visual Studio` that will launch Visual Studio for you and automatically launch the cloning of the repo.
<img width="1383" height="804" alt="GitHubVisualStudio" src="https://github.com/user-attachments/assets/27d84db0-a8db-4987-b718-7d0bfdfff1a9" />
