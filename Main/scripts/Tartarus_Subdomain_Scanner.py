import os
import socket
import threading
import random
import sys

def vex(cmd):
    subprocess.call(cmd, shell=True)

print ("\x1b[0;31mSelect An Option:")
print ("\x1b[1;37m[\x1b[1;32m1\x1b[1;37m] -Windows SubDomain Scanner ")
print ("\x1b[1;37m[\x1b[1;33m2\x1b[1;37m] -Linux SubDomain Scanner")

choice = raw_input("\x1b[0;31m[\x1b[1;37mroot\x1b[0;31m@\x1b[1;37mExploit\x1b[0;31m]\x1b[1;37m:")

if choice == '1':

        os.system('cls')

        subdomains = ["dc", "test", "api", "embed", "old", "play", "ns2", "server1", "server2", "gateway", "app", "status", "media", "ts3", "ns1", "host", "dashboard", "blog", "autodiscovery", "beta", "dev", "wiki", "autoconfig", "irc", "irix", "fileserver", "backup", "agent", "c2c", "login", "mssql", "mysql", "localhost", "nameserver", "netstats", "mobile", "mobil",  "ftp", "webadmin", "uploads", "transfer", "tmp", "support", "smtp0#", "smtp#", "smtp", "sms", "shopping", "sandbox", "proxy", "manager", "cpanel", "webmail", "forum", "driect- connect", "vb", "forums", "pop#", "pop", "home", "direct", "mail", "access", "admin", "oracle", "monitor", "administrator", "email", "downloads", "ssh", "webmin", "paralel", "parallels", "www0", "www", "www1", "www2", "www3", "www4", "www5", "autoconfig.admin", "autoconfig", "autodiscover.admin", "autodiscover", "sip", "msoid", "lyncdiscover"]
        os.system ('color D')
        url = raw_input('Enter Hostname:')
        os.system ('color C')

        for vex in subdomains:
                try:
                        host = str(vex) + "." + str(url)
                        ip = socket.gethostbyname(str(host))
                        print '[REAPER] ~> [LOADING] ~> [NAMESERVER] ' + host + ' ~> [IP] ~> ' + ip
                except:
                        pass

if choice == '2':

        subdomains = ["lupine", "slim", "chucks-laptop", "rowena-dell", "titan-server", "db1", "ns3", "ns2", "ns1", "consquentaffirmer", "mdsccaps1", "mdsccwamm2", "mdsccmmwa2", "pl", "oort", "lrid-alt", "mdrms", "mdsccex1", "lrid-nims2", "ralonso3", "africa", "jacaranda", "pcfs60", "vega", "angelmar", "asturias", "rafaromero", "stargazer", "helga", "pampa", "nautilus", "livianas", "gisws", "mdscc", "msfcvidyoportal", "border", "oighq", "lp345345", "decg.nasaoig-t", "fhfaoig", "gaooig", "gaooigt", "connect-ccd", "aerospace", "airspace", "www", "ldp", "border", "hcn", "esteem", "stab", "aab", "matb-files", "lms", "lmse", "trace", "prod-eosweb", "eosweb", "clarreo", "skyart", "science", "science-edu", "gewex-srb", "gewex-rfa", "flashflux", "capable", "discover-aq", "ceres-tool", "cain", "prod-www-cave", "www-cave", "POWER", "apply-develop", "cloud-object", "asd-www", "prod--asdcstatus", "subset", "asdc-arcgis", "geo-cape", "l0dup05", "earth-www", "sage", "www-calipso", "odisees", "punchingbag", "aero-fp", "ceres-erbeweb", "act-america", "arcstone", "korus-aq", "wag2-170-83", "wag2-171-15", "wag2-171-143", "xfr139", "www-air", "daedalus1", "www-gte", "cloudsway2", "enso", "scool", "reason-prod", "mynasadata", "larc", "mediaarchive", "kif3", "mediaarchive", "mescforyou", "masterplan", "ks-kdc-net1210", "aed.ksc", "kscsma.ksc", "nasarecycles", "kscpartnerships", "mediastream2", "eoc.ksc", "columbia", "procurement", "teerm", "ksccdc", "hewp", "ks-kdc-cf1210", "commercialcrew", "propellants", "ksc-lde.ndc", "tdglobal", "isru", "abfm", "kscoralhistory", "missionquiz", "nasaexchange", "pathways", "si", "specsintact", "ksc", "cryo.ksc", "ksc-fltops", "ndc", "ksc-vets", "extapps", "ksc", "kscwxarchive", "ksc", "mspwss01", "hadm", "afex01", "tscasp1", "molaeon", "aeonsp", "aeon", "aeonodte", "pdlprod3", "pdltest1", "pdltest3", "dnso1", "doehs001", "dnso2", "fohosc", "foums", "hosc", "msfc", "dc", "test", "api", "old", "aimslogin-sat.int", "aimslogin", "aimslogin-sat", "auto-api1-uat1", "auto-api1-uat2", "aims2", "alor-secureauto-cit1", "aimslogin2", "ns2", "play", "server", "server1", "server2", "gateway", "app", "media", "help", "embed", "status", "ns1", "host", "dashboard", "blog", "autodiscovery", "beta", "dev", "wiki", "autoconfig", "secure", "irc", "irix", "fileserver", "backup", "agent", "c2c", "ts3", "login", "mssql", "mysql", "localhost", "nameserver", "netstats", "mobile", "mobil",  "ftp", "webadmin", "uploads", "transfer", "tmp", "support", "smtp0#", "smtp#", "smtp", "sms", "shopping", "sandbox", "proxy", "manager", "cpanel", "webmail", "forum", "driect- connect", "vb", "forums", "pop#", "pop", "home", "direct", "mail", "access", "admin", "oracle", "monitor", "administrator", "email", "downloads", "ssh", "webmin", "paralel", "parallels", "www0", "www", "www1", "www2", "www3", "www4", "www5", "autoconfig.admin", "autoconfig", "autodiscover.admin", "autodiscover", "sip", "msoid", "lyncdiscover", "direct-connect", "private", "anycast", "panel", "imap", "portal", "record", "ssl","dns", "m", "client", "i", "x", "cdn", "images", "my", "java", "swf", "ns3", "ns4", "ns5", "mx", "server3", "vpn", "store", "zabbix", "cacti", "search", "nagios", "munin", "data", "stat", "stats", "preview", "phpmyadmin", "server1", "db", "demo", "gateway1", "gateway2", "remote", "svn", "git", "jira", "confluence", "jobs", "reader", "ovhprivate", "release", "Apache01", "IIS3", "IIs2", "Meeting", "Meeting-DFW", "Meeting-SAT", "PULSE", "Tlab-FICO", "www.Tlab-FICO", "VTC-DFW", "VTC-SAT", "Vtc", "abc", "abms", "abms-cap", "abms-cit1", "abms-cit2", "abms-cit3", "abms-dev1", "abms-dev2", "abms-dev3", "abms-ft", "abms-pdev1", "abms-pdev2", "abms-pdev3", "abms-prodsupt", "abms-staging", "abms-uat1", "abms-uat2", "abms-uat3", "access01", "accessgateway-model", "accessgateway-prod", "accountaccess", "www.accountaccess", "capacity.accountaccess", "system.accountaccess", "uat.accountaccess", "adfs", "www.adfs", "adfsd", "adfsm", "adfsp", "adfsp-dfw", "advantage-amp-prod", "aih-externalaccounts-sso-nonprod", "aims", "aims-ag", "aims-ag-a", "aims-ag-b", "aims-dfw", "www.aims-dfw", "aims-sat", "www.aims-sat", "aims2", "www.aims2", "aims3", "aims3-a", "aims3-b", "aimsfederate", "aimsidm-model", "aimsidm-prod", "aimslogin", "aimslogin-dfw", "www.aimslogin-dfw", "aimslogin-model", "aimslogin-prod", "aimslogin-sat", "www.aimslogin-sat", "aimslogin2", "www.aimslogin2", "aimslogin3", "aimslogin3-a", "aimslogin3-b", "alertcenter", "www.alertcenter", "click.alerts", "image.alerts", "mta.alerts", "mta2.alerts", "view.alerts", "allydealerleads", "allyspf", "alor-edgelogs", "alor-m-staging", "alor-m-uat2", "alor-secure-cit", "alor-secure-cit3", "alor-secure-fix", "www.alor-secure-fix", "alor-secure-pdev", "alor-secure-proda", "alor-secure-prodb", "alor-secure-prodc", "www.alor-secure-prodc", "alor-secure-prodd", "www.alor-secure-prodd", "alor-secure-prody", "www.alor-secure-prody", "alor-secure-prodz", "www.alor-secure-prodz", "alor-secure-pspa", "alor-secure-pspb", "alor-secure-pspc", "www.alor-secure-pspc", "alor-secure-pspd", "www.alor-secure-pspd", "alor-secure-qa1", "www.alor-secure-qa1", "alor-secure-qa2", "www.alor-secure-qa2", "alor-secure-uat3", "alor-secureapi", "alor-secureapi-dev", "alor-secureapi-mod", "alor-secureapi-prodsupt", "alor-secureauto-cit1", "alor-secureauto-cit3", "alor-secureauto-prodsupt", "alor-secureauto-staging", "alor-secureauto-uat1", "alor-secureauto-uat3", "alor-securebanking", "alor-securebanking-staging", "alor-securedealer", "alor-secureupload", "alor-secureupload-cit", "alor-secureupload-cit1", "alor-secureupload-cit2", "alor-secureupload-cit3", "alor-secureupload-pdev", "alor-secureupload-proda", "www.alor-secureupload-proda", "alor-secureupload-prodb", "www.alor-secureupload-prodb", "alor-secureupload-prodsupt", "alor-secureupload-pspa", "alor-secureupload-pspb", "alor-secureupload-staging", "alor-secureupload-uat1", "alor-secureupload-uat2", "alor-secureupload-uat3", "alor-staging", "alor-www-cit", "alor-www-cit1", "alor-www-cit2", "alor-www-cit3", "alor-www-pdev", "alor-www-pspa", "alor-www-pspb", "alor-www-uat2", "amplify", "www.amplify", "api", "api-cia", "api-cia-cap", "apiaccess", "www.apiaccess", "apm-beta", "www.apm-beta", "apm-dv", "apm-prodb", "www.apm-prodb", "appdeum", "appdeum-mod", "archive", "www.archive", "auto-amp-bf1", "auto-amp-cap1", "auto-amp-cit1", "auto-amp-cit2", "auto-amp-cit3", "auto-amp-dev1", "auto-amp-dev2", "auto-amp-dev3", "auto-amp-ps1", "www.auto-amp-ps1", "auto-api1", "auto-api1-a", "auto-api1-b", "auto-api1-bf1", "auto-api1-cap1", "auto-api1-cap1-a", "auto-api1-cap1-b", "auto-api1-cit1", "auto-api1-cit2", "auto-api1-cit3", "auto-api1-dev1", "auto-api1-dev2", "auto-api1-dev3", "auto-api1-ps1", "auto-api1-ps1-a", "auto-api1-ps1-b", "auto-api1-uat1", "auto-api1-uat2", "auto-api2", "auto-api2-a", "auto-api2-b", "auto-api2-bf1", "auto-api2-cap1", "auto-api2-cap1-a", "auto-api2-cap1-b", "auto-api2-cit1", "auto-api2-cit2", "auto-api2-cit3", "auto-api2-dev1", "auto-api2-dev2", "auto-api2-dev3", "auto-api2-ps1", "auto-api2-ps1-a", "auto-api2-ps1-b", "auto-api2-uat1", "auto-api2-uat2", "auto-ws", "autodiscover", "autodiscover-sat", "autogoldcupsweepstakes", "autosweepstakes", "mod.awsccap", "modeast.awsccap", "prod.awsccap", "prodeast.awsccap", "prodwest.awsccap", "backofficeapi-cap1-dfw", "backofficeapi-cap1-sat", "backofficeapi-dfw", "backofficeapi-sat", "backofficeapi-uat1", "backofficeapi-uat2", "balloon", "bank", "bap1-dev1", "bapi-cit1", "bapi-cit2", "bapi-dev1", "bapi-dev2", "bastion", "bdgsupport", "billpay", "bits-acm-ws-nonprod", "www.bits-acm-ws-nonprod", "bits-acm-ws-prod", "bm-secureauto", "bridgerinsight", "bridgerinsight-mod", "capacity-accountaccess", "capacity-dealerservices", "chat", "chat-dev", "chat-mod", "clarity", "clientauth-fiserv-prodb", "www.clientauth-fiserv-prodb", "clientauth-fiserv-uat1a", "www.clientauth-fiserv-uat1a", "clientauth-fiserv-uat1b", "www.clientauth-fiserv-uat1b", "clientauth-fiserv-uat2", "www.clientauth-fiserv-uat2", "secureupload.dr", "gddc-m", "midacod-model", "community", "community.communitytest", "confirmitmail", "cons-auto-api-cit", "www.cons-auto-api-cit", "cons-auto-api-dev", "www.cons-auto-api-dev", "cons-auto-api-ps", "cons-auto-api-uat", "covisintsamlsigning", "cap.cps", "st.cps", "uat.cps", "creditapp", "capacity.creditapp", "crm-jcaps", "crm-jcaps-cap", "crm-jcaps-ps", "crm-jcaps-uat", "csr-access", "www.csr-access", "css", "customerforum", "www.customerforum", "dealerservices", "www.dealerservices", "capacity.dealerservices", "system.dealerservices", "uat.dealerservices", "dfw1rapif011", "dfw1rapif012", "dfw1rapifapp011", "dfw1rapifapp012", "dfw1rapifbp011", "dfw1rapifbp012", "dfw1rapifmisc011", "dfw1rapifmisc012", "discloser-test", "dr", "www.dr", "abms.dr", "video.dr", "secure.dr", "securebanking.dr", "dr-csr-access", "early-terminations-dealer", "early-terminations-dealer-pp", "edge1", "edge2", "edgelogs", "www.edgelogs", "edr", "click.email", "image.email", "mta.email", "pages.email", "www.pages.email", "view.email", "enterpriseregistration", "esb-dev", "www.evault", "model.evaultext", "ews", "ex2016", "exo", "www.exo", "explore-products-rates", "dev.explore-products-rates", "facebook", "fundstransfers", "fundstransfers-cap", "www.fundstransfers-cap", "fundstransfers-sit", "gddc", "gddc-dfw", "gddc-m", "gddc-sat", "gns1", "gns2", "gns3", "gns4", "gns5", "gns6", "gns7", "gns8", "go", "www.go", "grc", "home", "prod.iam", "ism.ibm", "idmapi-acm-sso-nonprod", "insights", "www.insights", "inspections", "www.inspections", "sit.inspections", "test.inspections", "www.test.inspections", "testftp.inspections", "www.testftp.inspections", "training.inspections", "int", "www.int", "SAMApplication.int", "aapdswb-mod.int", "aims.int", "aims-dfw.int", "aims-sat.int", "aimslogin.int", "aimslogin-dfw.int", "aimslogin-sat.int", "api-out-gtw-bckend-cap1.int", "api-out-gtw-bckend-cit1.int", "api-out-gtw-bckend-cit2.int", "api-out-gtw-bckend-cit3.int", "api-out-gtw-bckend-dev1.int", "api-out-gtw-bckend-dev2.int", "api-out-gtw-bckend-dev3.int", "api-out-gtw-bckend-prd.int", "api-out-gtw-bckend-ps1.int", "api-out-gtw-bckend-uat1.int", "api-out-gtw-bckend-uat2.int", "bdgsupport.int", "bdgtesting1.int", "bdgtesting2.int", "bdgtesting3.int", "bdgtesting4.int", "bdgtesting5.int", "bdgtesting6.int", "bridgerinsight-mod.int", "cap1-servicingautomation.int", "cs-docmanagement.int", "cs-docmanagement-cap.int", "cs-docmanagement-flnt.int", "cs-docmanagement-ps.int", "cs-docmanagement-troy.int", "cs-docmanagement-uat1.int", "cs-docmanagement-uat2.int", "dfw1napise003.int", "www.dfw1napise003.int", "esb.dr.int", "esb.int", "esb-cap.int", "esb-cit.int", "esb-cit1.int", "www.esb-cit1.int", "esb-cit2.int", "www.esb-cit2.int", "esb-cit3.int", "esb-dev1.int", "www.esb-dev1.int", "esb-dev2.int", "www.esb-dev2.int", "esb-dev3.int", "esb-dev5.int", "www.esb-dev5.int", "esb-dev6.int", "esb-fix.int", "www.esb-fix.int", "esb-ft.int", "www.esb-ft.int", "esb-pdev.int", "www.esb-pdev.int", "esb-proda.int", "esb-prodb.int", "esb-prodsupt.int", "www.esb-prodsupt.int", "esb-staging.int", "esb-uat1.int", "www.esb-uat1.int", "esb-uat2.int", "www.esb-uat2.int", "esb-uat3.int", "fis-bridgerinsight-mod.int", "fis-bridgerinsight-prod.int", "guestaccess.int", "guestauth.int", "hemtesting.int", "hist-csr.int", "www.hist-csr.int", "invest-cap.int", "interstitial.invest-cap.int", "live.invest-cap.int", "live-streamer.invest-cap.int", "sp-live.invest-cap.int", "invest-mobile-dev.int", "www.invest-mobile-dev.int", "invest-mobile-qa.int", "www.invest-mobile-qa.int", "live.invest-prod.int", "live-streamer.invest-prod.int", "live.invest-psp01.int", "invest-qa01.int", "investor.invest-qa01.int", "investor-admin.invest-qa01.int", "live.invest-qa01.int", "live-streamer.invest-qa01.int", "live.invest-qa02.int", "live.invest-qa03.int", "live.invest-qa04.int", "live.invest-qa05.int", "live.invest-qa06.int", "m.int", "www.m.int", "m-aims.int", "m-aims-dfw.int", "m-aims-sat.int", "m-aimslogin.int", "m-aimslogin-dfw.int", "m-aimslogin-sat.int", "m-cit2.int", "nus-txdfw1-sa-4400-001.int", "ocp-devops.int", "ocp-prod1.int", "ocp-prod2.int", "ocp-qa.int", "owa.int", "peoplesofthr.int", "poc4.int", "psp-servicingautomation.int", "rpad.int", "sam-dev1.int", "sam-dev2.int", "sam-dev3.int", "sam-dev4.int", "sat1napise003.int", "www.sat1napise003.int", "sat1oapvp016.int", "www.sat1oapvp016.int", "secure-cap.int", "secure-cit1.int", "www.secure-cit1.int", "secure-cit2.int", "www.secure-cit2.int", "secure-cit3.int", "secure-dev1.int", "www.secure-dev1.int", "secure-dev2.int", "secure-dev3.int", "secure-dev5.int", "www.secure-dev5.int", "secure-dev6.int", "secure-fix.int", "www.secure-fix.int", "secure-ft.int", "www.secure-ft.int", "secure-pdev.int", "www.secure-pdev.int", "secure-uat1.int", "www.secure-uat1.int", "secure-uat2.int", "www.secure-uat2.int", "secure-uat3.int", "secureauto-cap.int", "www.secureauto-cap.int", "secureauto-cit3.int", "www.secureauto-cit3.int", "secureauto-dev2.int", "secureauto-dev3.int", "www.secureauto-dev3.int", "secureauto-fix.int", "www.secureauto-fix.int", "secureauto-uat3.int", "www.secureauto-uat3.int", "secureupload.int", "www.secureupload.int", "secureupload-cap.int", "secureupload-cit1.int", "secureupload-cit2.int", "secureupload-cit3.int", "secureupload-dev1.int", "secureupload-dev2.int", "secureupload-dev3.int", "secureupload-dev5.int", "secureupload-dev6.int", "secureupload-fix.int", "secureupload-ft.int", "secureupload-proda.int", "www.secureupload-proda.int", "secureupload-prodb.int", "www.secureupload-prodb.int", "secureupload-prodsupt.int", "secureupload-uat1.int", "secureupload-uat2.int", "secureupload-uat3.int", "servicingautomation.int", "staging.int", "suppliergetvpn.int", "sys1-servicingautomation.int", "sys2-servicingautomation.int", "uat1-servicingautomation.int", "uat2-servicingautomation.int", "mfa.vpn.int", "mfa-dfw.vpn.int", "mfa-sat.vpn.int", "mobile.vpn.int", "mobile-dev.vpn.int", "mobile-dfw.vpn.int", "mobile-sat.vpn.int", "portal.vpn.int", "portal-dev.vpn.int", "portal-dfw.vpn.int", "portal-sat.vpn.int", "wapi-cit1.int", "wapi-cit2.int", "wapi-cit3.int", "wapi-uat1.int", "wapi-uat2.int", "wires-uat.int", "www.wires-uat.int", "www-cap.int", "www-cit.int", "www-cit1.int", "www-cit2.int", "www-cit3.int", "www-dev1.int", "www-dev2.int", "www-dev3.int", "www-dev5.int", "www-dev6.int", "www-fix.int", "www-ft.int", "www-pdev.int", "www-proda.int", "www-prodb.int", "www-prodsupt.int", "www-uat1.int", "www-uat2.int", "www-uat3.int", "invest", "autodiscover.invest", "error.invest", "firebird.invest", "live.invest", "live-cap2.invest", "logging.invest", "maintenance.invest", "mobile-qa.invest", "phoenix.invest", "raf.invest", "snowplow-collector.invest", "xchange.invest", "invest-data", "www.invest-data", "invest-preprod", "iscoe", "www.jcaps-pp", "learn", "link", "lyncdiscover", "m", "m-aims", "m-aims-ag", "m-aims-ag-a", "m-aims-ag-b", "m-aims-dfw", "www.m-aims-dfw", "m-aims-sat", "www.m-aims-sat", "m-aims2", "www.m-aims2", "m-aims3", "m-aims3-a", "m-aims3-b", "m-aimsfederate", "m-aimslogin", "m-aimslogin-dfw", "www.m-aimslogin-dfw", "m-aimslogin-sat", "www.m-aimslogin-sat", "m-aimslogin2", "www.m-aimslogin2", "m-aimslogin3", "m-aimslogin3-a", "m-aimslogin3-b", "m-apm2", "m-cap", "m-cit1", "m-cit1-int", "m-cit2", "m-cit2-int", "m-cit3", "m-cit3-int", "m-dev1", "m-dev1-int", "m-dev2", "m-dev2-int", "m-dev3", "m-dev3-int", "m-fix", "m-fix-int", "m-prodsupt", "m-staging", "m-uat1", "m-uat2", "m-uat3", "mail", "maintenance", "maintenance-mod", "media", "meet", "meeting", "meeting-sat", "metrics", "mftlec", "www.mftlec", "mftlec-pp", "www.mftlec-pp", "mftm", "mftp", "www.mftp", "mftp-dfw", "mftp-sat", "mftstd", "www.mftstd", "mftstd-pp", "www.mftstd-pp", "mi", "midacod", "mig1", "mig2", "mig3", "mig4", "mlr", "mlr-dev2", "mlr-sit", "mlr-uat", "mmpp-aaos-nonprod", "mobile-cap1-dfw", "mobile-cap1-sat", "mobile-dfw", "mobile-ps-dfw", "mobile-ps-sat", "mobile-sat", "mod-owa", "musiccity", "mx01", "www.mx01", "mx02", "www.mx02", "my", "myauto", "www.myauto", "mau.myauto", "www.mau.myauto", "vsc.myauto", "www.vsc.myauto", "mobile.ensenta.nonprod", "www.mobile.ensenta.nonprod", "ns1", "ns11", "ns12", "ns13", "ns14", "ns2", "ns3", "ns4", "nus-txdfw1-sa-4400-001", "occ", "online-application", "online-application-ws", "origin-m", "origin-www-proda", "origin-www-prodb", "owa", "www.owa", "payment-admin", "peoplesofthr", "poc", "portal", "portal-mdl", "peoplesofthr.prf", "client.nonprod.prism", "www.client.nonprod.prism", "client.prod.prism", "prism-cmx-osb-cap", "prism-cmx-osb-prod", "prism-cmx-osb-pspdr", "prism-cmx-osb-sit", "prism-cmx-osb-uat", "prism-cmx-prod", "prism-ins-osb-cap", "prism-ins-osb-prod", "prism-ins-osb-uat", "prism-ins-uat", "prism-osb-cap", "prism-osb-prod", "prism-osb-psp", "prism-osb-pspdr", "prism-osb-sit", "prism-osb-uat", "prism-rtl-osb-cap", "prism-rtl-osb-dev", "prism-rtl-osb-prod", "prism-rtl-osb-pspdr", "prism-rtl-osb-sit", "prism-rtl-osb-uat", "prism-rtldefi-osb-cap", "prism-rtldefi-osb-prod", "prism-rtldefi-osb-pspdr", "prism-rtldefi-osb-sit", "prism-rtldefi-osb-uat", "prism-srvgen-osb-cap", "prism-srvgen-osb-prod", "prism-srvgen-osb-pspdr", "prism-srvgen-osb-uat", "prism-wic-admin-cap", "prism-wic-admin-sit", "prism-wic-admin-uat", "prism-wic-cap", "www.prism-wic-cap", "prism-wic-jms-cap", "prism-wic-jms-prod", "prism-wic-jms-pspdr", "prism-wic-jms-sit", "prism-wic-jms-uat", "prism-wic-osb-cap", "prism-wic-osb-prod", "prism-wic-osb-pspdr", "prism-wic-osb-sit", "prism-wic-osb-uat", "prism-wic-sit", "www.prism-wic-sit", "prism-wic-uat", "www.prism-wic-uat", "cmx.prod", "www.cmx.prod", "dealercrm.prod", "dps.prod", "dpscrm.prod", "prodsupt-accountaccess", "prodsupt-dealerservices", "pulse", "pulse-dfw", "pulse-mod", "pulse-sat", "raservice", "research", "www.research", "reviews", "sa", "sam-cap-adobe-vi", "sat1rapif011", "sat1rapif012", "sat1rapifapp011", "sat1rapifapp012", "sat1rapifbp011", "sat1rapifbp012", "sat1rapifmisc011", "sat1rapifmisc012", "sso.branch.uat.securdealerportal", "secure", "secure-cap", "secure-cit", "secure-cit1", "secure-cit2", "secure-cit3", "secure-dev1", "secure-dev2", "secure-dev3", "secure-dev5", "secure-dev6", "secure-dev7", "secure-fix", "secure-ft", "secure-pdev", "secure-predev1", "secure-predev2", "secure-prodsupt", "secure-qa1", "secure-qa2", "secure-sprint1", "www.secure-sprint1", "secure-sprint2", "secure-sprinttest", "secure-staging", "secure-uat1", "secure-uat2", "secure-uat3", "secureapi", "secureapi-dev", "secureapi-mod", "secureapi-prodsupt", "secureauto", "www.secureauto", "secureauto-cit1", "www.secureauto-cit1", "secureauto-cit2", "secureauto-cit3", "www.secureauto-cit3", "secureauto-prodsupt", "www.secureauto-prodsupt", "secureauto-staging", "www.secureauto-staging", "secureauto-uat1", "secureauto-uat2", "secureauto-uat3", "www.secureauto-uat3", "securebanking", "securebanking-prodsupt", "securebanking-staging", "securebanking-uat1", "securebanking-uat2", "securebanking-uat3", "securebillpay", "securebillpay-sit", "securedealer", "www.securedealer", "alor-uat.securedealer", "alor-uat2.securedealer", "capacity.securedealer", "cit.securedealer", "dev.securedealer", "prodsupt.securedealer", "pw.securedealer", "capacity.pw.securedealer", "prodsupt.pw.securedealer", "saml.securedealer", "capacity.saml.securedealer", "sit.securedealer", "system.securedealer", "uat.securedealer", "www.uat.securedealer", "uat2.securedealer", "www.uat2.securedealer", "securedealer-proda", "securedealer-prodb", "securedealerportal", "www.securedealerportal", "admin.securedealerportal", "www.admin.securedealerportal", "any.securedealerportal", "sso.branch.securedealerportal", "cap.securedealerportal", "www.cap.securedealerportal", "admin.cap.securedealerportal", "sso.branch.cap.securedealerportal", "identity.cap.securedealerportal", "sso.cap.securedealerportal", "tib.cap.securedealerportal", "cit.securedealerportal", "www.cit.securedealerportal", "admin.cit.securedealerportal", "sso.branch.cit.securedealerportal", "identity.cit.securedealerportal", "sso.cit.securedealerportal", "tib.cit.securedealerportal", "identity.securedealerportal", "www.identity.securedealerportal", "pp.securedealerportal", "sit.securedealerportal", "www.sit.securedealerportal", "admin.sit.securedealerportal", "sso.branch.sit.securedealerportal", "identity.sit.securedealerportal", "sso.sit.securedealerportal", "tib.sit.securedealerportal", "splash.securedealerportal", "sso.securedealerportal", "www.sso.securedealerportal", "tib.securedealerportal", "www.tib.securedealerportal", "uat.securedealerportal", "www.uat.securedealerportal", "admin.uat.securedealerportal", "sso.branch.uat.securedealerportal", "identity.uat.securedealerportal", "sso.uat.securedealerportal", "tib.uat.securedealerportal", "webdav.uat.securedealerportal", "webdav.securedealerportal", "www.webdav.securedealerportal", "securedeposit", "securedeposit-sit", "securepopmoney", "www.securepopmoney", "securepopmoney-sit", "securesmartcash", "www.securesmartcash", "capacity.securesmartcash", "securetransfer", "www.securetransfer", "securetransfer-sit", "www.securetransfer-sit", "secureupload", "secureupload-cap", "secureupload-cit1", "secureupload-cit2", "secureupload-cit3", "secureupload-dev1", "secureupload-dev2", "secureupload-dev3", "secureupload-dev5", "secureupload-dev6", "secureupload-dev7", "secureupload-fix", "secureupload-ft", "secureupload-pdev", "secureupload-prodsupt", "secureupload-staging", "secureupload-uat1", "secureupload-uat2", "secureupload-uat3", "sec.services-dev", "sec.services-mod", "sec.services-qa", "sharepoint-dfw", "www.sharepoint-dfw", "smartauctionreports", "www.smartauctionreports", "vip.se.smartauctionreports-mod", "smartcash", "capacity.smartcash", "smetrics", "smproxy-pulse", "smtp", "splurgealert", "st-sa", "www.st-sa", "st-sa2", "staging", "www.staging", "PULSE.stg", "subidp-federation-sso-prod", "supplier", "supplier-dfw", "supplier-mod", "supplier-sat", "suppliergetvpn", "survey", "www.survey", "system-dealerservices", "dealercrm.test", "www.dealercrm.test", "dps.test", "dpscrm.test", "test-Hem", "test-Hem-EV", "www.test-Hem-EV", "test-Hem-standard", "www.test-Hem-standard", "tm", "tp-cap", "tp-dev", "tp-mod", "tp-prod", "tp-qa", "ts-sa2", "cmx.uat", "peoplesofthr.uat", "uat-dealerservices", "uat-sa", "www.uat-sa", "uat-sa2", "uat-securesmartcash", "www.uat-securesmartcash", "upgrade", "vanitymod-dmz", "video", "video-dev", "video-staging", "vpc-cap", "vpc-prod", "vpn", "atl.vpn", "www.atl.vpn", "dfw.vpn", "www.dfw.vpn", "employee.vpn", "mfa.vpn", "mfa-dfw.vpn", "mfa-sat.vpn", "mobile.vpn", "mobile-dev.vpn", "mobile-dfw.vpn", "mobile-sat.vpn", "portal.vpn", "www.portal.vpn", "portal-dev.vpn", "portal-dfw.vpn", "portal-sat.vpn", "sat.vpn", "www.sat.vpn", "supplier.vpn", "vsc", "www.vsc", "vsc-cap", "www.vsc-cap", "vtc", "wapi", "www.wapi", "wapi-acceptance-nma", "wapi-cap1-dfw", "wapi-cap1-sat", "wapi-cit-nma", "www.wapi-cit-nma", "wapi-cit1", "wapi-cit1-nma", "wapi-cit2", "wapi-cit2-nma", "wapi-cit3", "wapi-cit3-nma", "wapi-dev1", "wapi-dev2", "wapi-dev3", "wapi-dfw", "wapi-integration-nma", "wapi-ps", "www.wapi-ps", "wapi-ps-dfw", "wapi-ps-sat", "wapi-sat", "wapi-uat-nma", "www.wapi-uat-nma", "wapi-uat1", "wapi-uat1-nma", "wapi-uat2", "wapi-uat2-nma", "web-cap1-dfw", "web-cap1-sat", "web-dfw", "web-ps-dfw", "web-ps-sat", "web-sat", "webcsr-cit1", "webcsr-uat1", "www.webcsr-uat1", "webcsr-uat2", "webcsr-uat3", "www.webcsr-uat3", "webseries", "wvw", "www.wvw", "www-cap", "www-cit1", "www-cit2", "www-cit3", "www-dev1", "www-dev2", "www-dev3", "www-dev5", "www-dev6", "www-dev7", "www-dr", "www-fix", "www-prodsupt", "www-test1", "www-test2", "www-uat1", "www-uat2","www-uat3"]
        url = raw_input('\x1b[1;36mEnter Hostname\x1b[0;31m:\x1b[1;37m')

        for vex in subdomains:
                try:
                        host = str(vex) + "." + str(url)
                        ip = socket.gethostbyname(str(host))
                        print '\x1b[1;31m' + host + '\x1b[1;37m:\x1b[1;36m' + ip
                except:
                        pass


