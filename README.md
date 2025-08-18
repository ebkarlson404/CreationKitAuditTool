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
works on plugin files whose names end with `.ESP`, it places the plugin-specific files in a directory named `MyMod.ESP`.  However,
when the plugin is published Creation Kit creates a plugin file with an extension of `.ESM` so when Starfield loads the `.ESM` plugin
file, it will look for the plugin-specific files in a directory named `MyMod.ESM`, which does not exist.

The Creation Kit Audit Tool will automatically detect when plugin files reside in a `MyMod.ESP` directory and will replicate those
files into a corresponding `MyMod.ESM` directory to use for the generated ACHLIST packing list.  This will result in a
`BA2` file that is ready to ship with the resulting `.ESM` plugin file.
## PC and XBox WEM Files
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

Once this is done, when one uses the `Audio | Process Local Voice WAVs` or `Audio | Build Soundbank for Active File` tool in Creation
Kit to process `.WAV` files into `.WEM` files, it will create *both* the PC and XBox WEM files in a single pass, placing the XBox WEM
files into the alternate directory paths specified in the `CreationKitCustom.ini` file above.  One can then configure that
`XBox WEM Path` in the Creation Kit Audit Tool and when the tool generates the platform-specific ACHLIST packing lists, the PC
ACHLIST file will pack the WEM files from the standard directory tree and the XBox ACHLIST file will pack the WEM files from
the alternate XBox directory tree.

# Quick Start Instructions
1. Ensure that you have a properly deployed Starfield Creation Kit
2. If you will be generating WEM files as part of your plugin work, ensure that you have setup the `Audio` configuration block as detailed above
3. Start up the Creation Kit and load up your plugin
4. Start up the Creation Kit Audit Tool and tell it which plugin you are working on.  If you have worked on this plugin with the Creation Kit Audit Tool before, the audit log for the plugin will be initialized from the previous run.  If this is the first time that you're using the Creation Kit Audit Tool for this plugin, you can load your old ACHLIST file to initialize the set of files to include.
5. Click `Start` in the Creation Kit Audit Tool
6. Go back to your Creation Kit and work on your plugin
7. When you are ready to package the plugin, go back to the Creation Kit Audit Tool and click on the `Generate` button to create the two platform-specific ACHLIST files.  They will be created in your `Documents\My Games\Starfield\CreationKitAuditTool` directory.
8. Go back to Creation Kit and use the `Archive` tool to pack your `BA2` files by importing the ACHLIST files that were stored in your `Documents\My Games\Starfield\CreationKitAuditTool` directory.

You can suspend the audit processing at any time by clicking on the `Stop` button in the Creation Kit Audit Tool and then resume audit
processing by clicking on `Start` again.

Once the Creation Kit Audit Tool has been used for a given plugin, it will save the manifest of all files detected during the audit
session in a file named *MyMod.manifest* in your `Documents\My Games\Starfield\CreationKitAuditTool` directory.

If you have an existing ACHLIST file for your plugin, you can initialize the manifest in the Creation Kit Audit Tool by using the
`Import` button to merge the contents of the ACHLIST file into the plugin's manifest file.

Once the manifest file has been created for a given plugin, the Creation Kit Audit Tool will use this manifest file to reload the audit
log for that plugin the next time that the audit tool is used to monitor activity for that plugin.

This manifest file is nothing more than a list of all the discovered files with one file per line.  One can create/edit a
manifest file directly by hand if one wants to manually setup the initial audit log for a plugin.
# Build Configuration
One can download the project files from GitHub and build the tool locally if one so desires.  In order to do so
one must first prepare their build environment as follows:
1. Download and install [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)
2. Go into `Tools | Get Tools and Features ...` and ensure that you have the `Desktop development with C++` feature installed with the `C++/CLI support for v143 build tools` package included.  See the third-party video here for a walk-through: [Create your first C++ GUI WIndows Form using Visual Studio 2022](https://youtu.be/AINCOpXma6M?t=90)
3. Go into `Git | Clone repository` to pull down the repo from GitHub: `https://github.com/ebkarlson404/CreationKitAuditTool.git`
