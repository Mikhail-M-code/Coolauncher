import sys
import subprocess
import minecraft_launcher_lib

minecraft_version = sys.argv[1]
minecraft_directory = sys.argv[2]
java_directory = sys.argv[3]
jvm_arguments = sys.argv[4]
username = sys.argv[5]

if jvm_arguments == "non":
    options = {
        'username': username,
        'uuid': '',
        'token': '0',
        'executablePath': java_directory
    }
else:
    options = {
        'username': username,
        'uuid': '',
        'token': '0',
        'jvmArguments': jvm_arguments.split(),
        'executablePath': java_directory
    }

minecraft_launcher_lib.install.install_minecraft_version(versionid = minecraft_version, minecraft_directory = minecraft_directory)

command = minecraft_launcher_lib.command.get_minecraft_command(version = minecraft_version, minecraft_directory = minecraft_directory, options = options)
subprocess.call(command)