import os
import ycm_core

flags = [
'-Wall',
'-Wextra',
'-Wno-long-long',
'-Wno-variadic-macros',
'-fexceptions',
'-DNDEBUG',
'-DUSE_CLANG_COMPLETER',
'-std=c++14',
'-x',
'c++',
# current Project
'-I./ImageReaderGUI/hdr/',
'-I./ImageReaderLibraries/hdr/',
# system
'-I/usr/include/',
'-I/usr/include/x86_64-linux-gnu',
# QT5
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtInputSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebView/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtDeviceDiscoverySupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtGamepad/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuick/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtSvg/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebEngine/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtConcurrent/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtXmlPatterns/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtLinuxAccessibilitySupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtBluetooth/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQml/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DInput/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtScxml/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtEglSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtScript/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtCLucene/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQmlDevTools/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtFontDatabaseSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DCore/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtFbSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtGlxSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtServiceSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuickTemplates2/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtEglFSDeviceIntegration/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPacketProtocol/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuickTest/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtSerialPort/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuickControls2/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtMultimedia/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtOpenGLExtensions/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtNetworkAuth/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtDesigner/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWidgets/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DLogic/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtThemeSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtGui/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtSensors/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtNetwork/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtHelp/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtAccessibilitySupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtXml/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DQuickRender/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtLocation/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtNfc/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DQuickExtras/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtScriptTools/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtTest/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtOpenGL/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPlatformHeaders/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuickWidgets/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtMultimediaWidgets/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtDesignerComponents/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQmlDebug/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtEventDispatcherSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtMultimediaQuick_p/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPlatformCompositorSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtSerialBus/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtDataVisualization/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPurchasing/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebSockets/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtCharts/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtSql/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtUiPlugin/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPositioning/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtUiTools/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DQuick/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DQuickInput/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtTextToSpeech/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebEngineWidgets/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebChannel/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DExtras/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtPrintSupport/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtDBus/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtCore/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/Qt3DRender/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtX11Extras/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtQuickParticles/',
'-I/home/ahussein/Qt5.8.0/5.8/gcc_64/include/QtWebEngineCore/',
]


# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]


def GetCompilationInfoForFile( filename ):
  # The compilation_commands.json file generated by CMake does not have entries
  # for header files. So we do our best by asking the db for flags for a
  # corresponding source file, if any. If one exists, the flags for that file
  # should be good enough.
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )


def FlagsForFile( filename, **kwargs ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = GetCompilationInfoForFile( filename )
    if not compilation_info:
      return None

    final_flags = MakeRelativePathsInFlagsAbsolute(
      compilation_info.compiler_flags_,
      compilation_info.compiler_working_dir_ )

    # NOTE: This is just for YouCompleteMe; it's highly likely that your project
    # does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
    # ycm_extra_conf IF YOU'RE NOT 100% SURE YOU NEED IT.
    try:
      final_flags.remove( '-stdlib=libc++' )
    except ValueError:
      pass
  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return { 'flags': final_flags }
