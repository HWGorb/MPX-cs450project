#include "Startup.h"

void startup(){
	int buffersize = 300;
	sys_req(WRITE,DEFAULT_DEVICE,"++++++++++++++++++++++++++++++++++~~~~~~~~:::=~~+=333+~~==~:~::~~~==++3333333333+=+=:~::::::,:::::~+3333333333333+++++++++++++++++++=~~==~~:~~=+~:::,::,,~=~::::,::,,,::,,,,:~,:,,,:::,,,,,,,,,,:..,,.~:\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"+++++++++++++++++++++++++++++++++~~+=+~+~~:~=~~++33333~~:+~:::~~~~+333333333333+=~~:~~:::,::,:,:::~~==33+3333333333+++++++++++++++=~~~~~:~::~~~:~~~::~::~~=:::,:,,,,,,,::,:,:,,::,:~:::,:,,,,,,:,~,,:,,~\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"++++++++++++++++++++++++++++++++==~+3=+3=~~~333=33+=++:::~::::::~+=3333333333333=~:~~~:::,,,,,:,::::~~=~++3333333333333++++++++++=~~~~~~~~~~:::::~::::::~~~~~:~:,,:,,:::~:::::::::~::,,::,:::,::,,,,,.,:\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"+++++++++++++++++++++++++++++++=+3++3=33=+==333+=~++~~:::~::::::~~+333333333333+~~=~::::,:,,,,,,,,:~~~====++333333333333++++++++++=+======::::::::::~::~~~~~:::,:~::,,:,:::::~~::::,:,:,,::,,:,:,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"++++++++++++++++++++++++++++33+333333+3333+3+333+~~~::::::::~:~:~=+33333333333+~~~~~:::::,,,,,:,,,:~=+=3333333333333333+++++++++++++++++=~~::::::::::~:::~~~::::,::,,::,,:,~:::::::::~::,:::::,:::,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"333333++++++++++++33++++3333333333333333333333+3+:::::~+::::::=~=~3+333333333+=:::~::::,,,,,,,::~:::=333333333+++++++++++++++++++++++++~~~~~:~~::~:::::::~~~::,::,:::,,,,:~,:,~::,:::::::::,,::,:,::,::,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"33333333++++++++++++++++333333333333333333+==+=~:::::=~+:::::::~==~~++3333333+~~::::::::::,:,,,,,::==3333333++++++++++++++++++++++++++=~~==~:~:::::::::::::~::~:,,,:,,,,~:::~~:,,:::::::::,,:,~,::,,,::,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"333333333+++++++++++++++++++33333333333333+=~~:::::::::=:::::~:~::::~=++3333+=~:::,,,,:,:::::,,:,,=:==+++++++++++++++++++++++++++++=~~~===~~::::::::::::::::~::,,,,,,:::,,::~:,,::::~::,,,,,,,,,,,,,,,,:\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"==+3333333++++++++++++++++3333333333333333+=~::::::::~=~~::~:=~~::::::~~~=+++~~~::::::::::::::,,:,::~~~++++++++++++++++++++++++++++~=~===~=~::::~::::::::::::,:,,,,:,,:::,:,,::::~::::::,,,::,,:,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"====+3333333++++++++++33333333333333333333+~~~::::::~=~~=::::===:::::::~~~++=~~~~~::::::::,:::,,,:::::~==++++++++++++++++++++++++++====~~:::::::~::~:,::,:::,,,,,,,,:,,,,,,:::::~~~:::::,,::,,:,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"======++3333333333++333333333333333333333+=~~+~:::~~~+~~=:::~++~::,,:,:::~~~::::::~:::::::,:,:,,,,:~:~:~=+++++++++++=+=+++++++++++++++=~~:::::::::,,:,,,,,,,,,,,,::::,,:::~:~~::::::::,:,:,:::,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"=~=========+3333333333333333333333333333++~==+=~~=+~++~~~:::~=+~:::,:::::::~::::::::::::~::,:,,,,,,::::~====++++==~:::::==++++++++++++~~~:::::::::,,,,,,,,,,,,,,,,,~,,,::,,,::::::::::,,,:,,,:,:,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"==============++33333333+++++++++++++++++=++++++=++++=~~::,,:~~:~:::::~:~~::::::~:~~::::~:,,:,:,,,,,:::::~~==~:::,,,,,,,,::=+++++++++++=:::~:::,:,::,:,:,,,,,,,,,:,,,:,,~:::::::,:::,:::,:,,:,,:,,,,,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~==============++++++++++++++++++++++++++++++++++++++=~:::::::~:~::::::::~~~:~::~~::::::::::,:,,,,,::::::::~,,,,,,..,,.,,,,:==++++++++=~:::::::::::::,,,,,,,,,::,,::::~::~:::::,:~:,,,:~::,,:::,,,,,,.,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~===========~========+++++++++++++++++==++++++++++++==:::~::::::~~::~~::::~::~::~:::~::~::::,,,,:,,::::::~~,,,,,,,,,...,..,,::=++++++~~~~~~::::,:::,:,,:::,,::::::::,,~~:::::~::,:::::,,~::::,::,,,,,..,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"===========~~~===============~============+++++++++~::~::=::,:::::::::::::::::~:::~~:~~~~::,:,,:,:::,,::::,,,,,,,,,,,,,,,,...,~=++++===~~~~::~,:,,:,::~::::~::~:,::::::,:~::~~:~:~:::~:::,,,,,,,,,.,,,..\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~==========~~=~===========~=~~================+++==~::::~~:::,::::::::~::::::::::::~~:~:::,::::~:,:::::::,,,..,,,,,,,,,,,,,..,,~++++++~~~~~:::::,,,,,:,::::::::::::::::~:~::::,,:::::,,:,,,,,,:,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~=~=======~==~===~==~~~~~~~~=====~=====~=~~~~==~::::::::::,,:,:::::::~:,:~::~:::::::,::::::,:,::::~~~~,,.,,,,,,,,,,,,,,,,,,,:==+++=~~~:,,::::::::,:::::,:::::::::,,,::::~~::::,~::,,,,,,,,,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~=~~~~~~~====~~=====~~~~~~~~===========~==~~~~~~:::::::::,,,,:,,:,:,::::::::::::::,::::::::,,,:::::~:~:...,,,,,,,,,,,,,,,,...,,====~~:::,,:::~::::::,:,::::::::::,:~~:~~:::::::::::::::,,,,,,:,,,,,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~~===~=======~~==~~~~~~~~=~~~~~~~~===~~~~~::::,::::::,,,,:::,,,,::,:~:::::::::::::~~~:,,:,:,:::::~,..,,,,,,,,..........,,,:~~~~~:::~:::::::::::::::::::,,,,,::,:,,:::::~,::,:,::,,,:,,,,,,,,,,.,,\n", &buffersize);	
	sys_req(WRITE,DEFAULT_DEVICE,"=~~~~~~~~~~~=~==~~=~~===~~~=~~~~~~~~~~~~~~~~~~~~::::::::::::,,,,:::,,,,,,:::::::::::::::::::::::::::::~:~...,,.....,,..,....,...,,:~~~~~~~::::::~:,,:::,,,:::,,,,,:,::::::::::::,,,,:,,:,,,,,,,,:,,.,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"=~~~~~~~~~~~~~~~=~~~~~~~=~~~~~~~~~~~~~~~~~~:~~::::::::::::::,,,,:::::,,:,:::::::::::::::::,::~::::::::~::..........,,,.,,,,,,..,..,~:::~~~:::::::::~:::,::,:::,::::,::~::~::,,,,,,,,,,,::,:,::,,:,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~=~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~,,.,,,,....:~~::~~:::~::::,:,,,,::,:,,::,:::::::::::::,:::,:::::::::::::,,.,.....,,,,,,,,,.....,.,:::::~~~:::::::::::::,::::,::,:::,::,:,::,,,,,,,:::::,,::::::,.....,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~=~~~~~~~~~~~~~~~=~~~~~~~~,,............,~::::::::::::,,,,,~:::::::::::::::::::::::~:,~~:~:::::~:::,,...,,,,,,,,,,,.,,..,..,,::~~:::~~~::::~:::::::::,~,,,:::::,::,:,,::,,:::::,,....,::::,,,..,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~~~~~~~~~~~~~~~=~~~~~~~,..................,::::::::,:,:,,,::::::::::::::,::::::::::::::::::::::::::.......,.........,..,..,.,~~::~:~~~~~~~~~::::::~~:~:::::::::::,,,..,,::,,,,,,,,,,,,,,,,,.....,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~~~~~~~~==~~~==~~~~~~~:,...................:::::::,:,,,:,,,:,,,,,:,:,,,,,::::::,::::::::::,~::~::::,.....,....,,.......,..,.,,,::~~~:~~~:~::~::~::::::,,..,,:::::::,,,,,,,,,,,,,,,,,,,,,,,,:,,..,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~=~~~~~~~~~=~~~~~~~~~~,.,................,.::::::::::,:,,,,:,::,,,:::,,,::::~:::~:,:::::::,::::~:~:,.............,,,.............~~~:~~::~::,,,,::::::,,,,,,,,,,,,,,,:,,,,,,,,,,,,,,,,,,,.,,,,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~=~~~~~~~=~~~~~~~~~~~~~~....................,.:::::::,:,,:,,,::,:,,,,,:::,:::::,:::::::::::::::::::,,...,.....,,,,,,,,...,,,.,..,....,.,:,:,,,,::,,,,,,,,,,::,,,,,,,,,,,,,,,.,......,,,,,,,,,,,,,..\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"::~~~~~~~~~~~~~~~~~~~~~~~~~~~....................,..::::::::,,,,,,::,,,,,,,,,,,,::~~:::::::::~::::::::,,,:,..,,...........,...,,..,.............,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..,,,,,,........\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~::~~~~~~~~~=~~~~~~~::~~~~~~~:...................:..,:::~::,,,,,:,,,,,,,,,:,:,,~::::::~~~~~:,,,,,,::::,:,~.....,.............,,,...,,.............,,,,,,,,,,,,,,,,,,,,,,,,,..........,,,,::::,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~=~~~~~~~===~~~~:::::~~~:,...................,..:::::,,,,,,::,,,,,,,,:,,,:,,:::::::~~:,,,,,,,,,,,::,:.....,............,,,.............,........,,,,,,,.........,,,,,.,,,,,,,,,,,,,,,,,,,,,,,,..,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"==~~~~~~~=~~~~~~~~~~~~~~~~~~~~~:......................,::,,,,,,,,,,,,,,,,,,,,,,:::::::::::~,:,,,,,,:::,,,:.......,,.........,,,,..................,.....,.,,,,,,,,,,,,,,,,,,,,,,,.,,.,.......,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~~=~~~~~~~~~~~~:~~~~~~::~.......................:,,,,,,,,,,,,,,,,,,,,:,,:::~~::::,,:::~::::::::~..........,...........,,,......................,,..,.......,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,..,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~==:~=~~~~~===~~~~::~:~::~~~............................,,,,,,,,,,,,,,,:,.::::,,,:::,::::,:::::::.............,,.........,,,.................,.......,,,,,,,,,,,,,,,,.......,,,..,,,.,,,,,,,,,,,....\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~~~~~~~:~~~~~~~:~~~~~::~::~:::................................,,:,,,:,,,,,,,,::::,,:,::::::~::::,................,,,.......,...............................,,,,,,,,,,,,,,........,,,:,:::::~::~:::,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,":~~~~:~:~~:::~:~~:=~~~~~~::::::~..............,,.,,.........,,........,,,,,,::,.:::,,,,,::,:::::....................,,,...,...,.............................:::::::::::::,,,::,::::~::,::::~~~~~~~~~:...\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~~~:~~~~:~:::~::::~~~~~:::::~::..,......,,,..,..,,,,.....,..,...........,,,,,,::,:::,:,:,:,::::............................................................,:::::,,:::,:::::::,:::::~~~~~~~~~~:~~~~~~.,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~:::~::~:~:::~::::::~~~~~~~::~::,,,,,,,,,.....,,.,,.,......,.............,,,,:::,:,,::::::,::::............................................................,.::::~,,::::,,::::::::::~~~~:~:~~~::~~~~~,.,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~:::~~~~~:::::~~~~~~~::~~~~,::,,,,,,......,..,,..........,,...............,,.,,:,:::::::~:::,,,..............................................................::::,:,:,::,,,:::::~~~~~:~~~~~~~~:~:~~~:,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,":::::~::~~::~~~~~:~~~~::::~:,,,,,,.,.,,..........,.........................,..::,::,,,:~::::::,:,........................................................,...,:::::::::::::::::,,,,,,,..,,,,,,,,,,,,,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,":~:~:::::~::::~::::~~~~~~~,.,,,.,.,.,,...,.....,..,,.......................,,,:~,:~::::~:~::::::,............................................................,,,,,,,,,,,,,,.,,,.............,...,.,,,.,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~::::::::~~~~::::~:::~~~,,.,,,.,.,,,,.......................................,::~:::,:::::::::::::......................................................,.......,,,,,,,,,,,,,,,,,,,..,,,,,,,,,,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~::::,:::~~~::~~::::::,,,...,.,,,..,.,.......,,...........................:.::~,:,:::~~~:::::,:,,..................................................,...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"~:~~,,:~:::~:::::~~~,.,.,,.,.,.,......,..................,................::,~,:,:,::::::,:::,,,:,...............................................,............,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,::,::::~::::.......................................................,,,,,,,::~::~~:,,,,.,,,,..........................................................,,,,,,,,,,,,,,,,..,,,,,,,,,,,,,,,,,,,,,,,,..\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,:::::::::......................................................,:,:,,:,:::~::~~:,,,,,,,...........................................................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..,,..,..\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,..,:,::::..........,...........................................,::::,:,:::::~:~~:,,,,.,............................................,......,........::,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,:~::.....................................................,,::::::::::::~~~,,..,............,......................................,...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,:~::.....................................................,,::::::::::::~~~,,..,............,......................................,...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,,,,......................................................,,:::::~::,:~~,,,,,.,...........................................,,.,.................::::::~~~:~~~~::::,,,,.,....................\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,..........................................................:::::~:~::,,,.,,,,,....,.,.....,......,.......................,,,,,,,,..........,...,.,,,,,,,,,,......,,,,::::::~~~:~:::::::::,,\n", &buffersize);	
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,...........................................................:::::~:,,,,,,,..,..........,...,,,,,,,,,.....................,,,,,,,,,,,,,,...,....,,,::,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,....,......................................................:::,,,,,,,,...............,,,,,,,,,,,,,,......,..............,,,,,,,,,,,,,,,,,,,.....,,,,,,,,,,,,,,.,.,,,,,,,,,,,,,,:,,,,,,:,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,,,..,,.....................................................,,,.,.,.,.................,,,,,,,,,,,,,,.....................,,,,,,,,,,,,,,,,,,,,,,..............,,........,.,,,,,,,,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,::,,,,:,,,,,..,,,.................................................,,,,,,,.......................,,,,,,,,,,,,,.....................,,,,,,,,,,,,,,,,,,....,,,.,,,,,,,.,,,,,.................,,....,,,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,:,,,:,,,,,,,,..,,,,.............................................,,,,,,,.,........................,,,,,,,,,,,,,........,.............,,,,,,,,,,,,,,,,,,,,:,:,,,,,,,,,...,,,,,,.,.....,,,,,.,,.........\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,::::,,,,,,,,,,.,,,,,.........................................,,,,,,.,,,.,..........,..........,....,,,,,,,,,,,.......................,,,,,,,,,,,,,,,.....,,,,,,,,,,,,,,,,,,,,,,,,,,........,,,,,......\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,:,,,,,,,,,,,,,,,,,,,,,,...................................,,,,,.,,.,.....,,........................,,,,,,,,,,........................,,,,,,,,,,:,,.,.,,,.,,,,,,,.,,,..,,,,,,,,,,,,,,,,,,,,,,,,,,,,..,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,,,,,,,,,,,,,,.,.........,..................,,,,,,,,.,...........,.......................,,,,,,,,,..........,.............,,,,,,,,,,,,..........,,,,,,,,,,,.....,,,,,,,.,...,...,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,,.,,,,,..............,,,,,,,,,...............,,..............,.......,,,,,,:::,,....,...............:,,,,,,,,,,,,,,..,....................,,,,,,,,,,,,,...,,,,,.....,,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",,,,,,,,,,,,,,......,,,,,,,,,.,,,,,..,,,...........,,,,,,,,,,,,.......................................,,,,,,,,::,,.................::,,,,,,,,,,,,,,,....,,...........................,,,...,,,,,,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,",..,,,,,,,,,..........,,,,..,...,,...,.,.......,,,,,,,,,,.................,...............,...,.......,,,,,,,,,,:,,..............,,,,,,,,,,,,,,,,,,.....,,,,................,,,...................,,,,.,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,".,,,,,,,,,,...........,,,,,........,.,,..,..,,,,,..,,,,..,.............,.......................,.,....,,,,,,,,,,,::,...........,,,,,,,,,,,,,,,,,.........,,,,.,,,,,,,.,,........,,,..,.,,,..............\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,".,,,,,,,,,............,,,,,.,.........,,..,,...,,,,,...............,................................,.,.,,,,,,,,::,,:.........,,,,,,,,,,,,,,,............,,,,,,,,.,,,,,,...............,..,,,..,,.......\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,".,,,,,,,,,............,,,.,,..,,....,,,...,...,..............,..................................,..,,,...,,,,,,,,,::,:......:,:,,,,,,,,,,,,,,.............,,,,,,,:,,,,,,,..................,....,,....,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,".,.,,,,,,...........,,,,............,..,,,,,,..............................................................,,,,,,,,::,,.,.::::::,,,,,,,,,,,....,......,,......,,,,,,,,,,,.................,,,,,,,.......\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"...,,,,,,............,,..,.....,,,,,,,.,,.,...,,,............................................,.........,....,,,,,,,,..,.,,::,,,,,,,,,,,......,,.,,,,.,...,...,,,:,,,,,,,,.............,,,,,,,,..,,,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"....,,,,,,.........,,.,,.....,,.,,,.,,,...................................................,...................,,,,..,..,,,,::,,,,,,.,,,.,.......,,,.,,,,,.,..,..,:,,,:::,:::,,,,......,....,.,,,,,,...,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"....,,,,...........,,..,,,,,,,,,.,,,,..........................,............................,,..................,...,,.....,:,,,,,,,,,.................,.,,,,,,,,.,,,..,,,:::,,,,:,,,,:,......,,,.,,,,,,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"......,,.............,.,,,,,.,,,.,..........................................................,............................,,,.,,,,,,,.......,..................,::,,,,,,,::,,,,,::,:,,::::,,,,:::,...,,,.\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"..................,,,,,,,,,,.,...................,..............................................................,,,..,,,..,.,.,,,,.........,.................:,,,,,::,:::::,,,::,::,,::,,:::,,::,,,,,:,:\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"...............,,,,,,,,,.,..............................................................,......................,,,,:,,.,.,....................................,,,,,,:~,,:::::::::::,,:::,,::::::,::,,:::\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"...........,,.,.,,,,..,..,............................,...............................,,.....................,:,,,,,,...,..,...,,................................,,,::::,,,:,::::::,,::,,..,,,,,,:::,,:,\n", &buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██╗░░██╗███████╗██╗░░░██╗  ░██████╗░█████╗░███╗░░░███╗██╗░░░██╗███████╗██╗░░░░░░░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██║░░██║██╔════╝╚██╗░██╔╝  ██╔════╝██╔══██╗████╗░████║██║░░░██║██╔════╝██║░░░░░░░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"███████║█████╗░░░╚████╔╝░  ╚█████╗░███████║██╔████╔██║██║░░░██║█████╗░░██║░░░░░░░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██╔══██║██╔══╝░░░░╚██╔╝░░  ░╚═══██╗██╔══██║██║╚██╔╝██║██║░░░██║██╔══╝░░██║░░░░░██╗\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██║░░██║███████╗░░░██║░░░  ██████╔╝██║░░██║██║░╚═╝░██║╚██████╔╝███████╗███████╗╚█║\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"╚═╝░░╚═╝╚══════╝░░░╚═╝░░░  ╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝░╚═════╝░╚══════╝╚══════╝░╚╝\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██╗░░░██╗░█████╗░██╗░░░██╗██╗██████╗░███████╗  ███████╗██╗███╗░░██╗░█████╗░██╗░░░░░██╗░░░░░██╗░░░██╗\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"╚██╗░██╔╝██╔══██╗██║░░░██║╚█║██╔══██╗██╔════╝  ██╔════╝██║████╗░██║██╔══██╗██║░░░░░██║░░░░░╚██╗░██╔╝\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"░╚████╔╝░██║░░██║██║░░░██║░╚╝██████╔╝█████╗░░  █████╗░░██║██╔██╗██║███████║██║░░░░░██║░░░░░░╚████╔╝░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"░░╚██╔╝░░██║░░██║██║░░░██║░░░██╔══██╗██╔══╝░░  ██╔══╝░░██║██║╚████║██╔══██║██║░░░░░██║░░░░░░░╚██╔╝░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"░░░██║░░░╚█████╔╝╚██████╔╝░░░██║░░██║███████╗  ██║░░░░░██║██║░╚███║██║░░██║███████╗███████╗░░░██║░░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"░░░╚═╝░░░░╚════╝░░╚═════╝░░░░╚═╝░░╚═╝╚══════╝  ╚═╝░░░░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚══════╝╚══════╝░░░╚═╝░░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"░█████╗░░██╗░░░░░░░██╗░█████╗░██╗░░██╗███████╗\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██╔══██╗░██║░░██╗░░██║██╔══██╗██║░██╔╝██╔════╝\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"███████║░╚██╗████╗██╔╝███████║█████═╝░█████╗░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██╔══██║░░████╔═████║░██╔══██║██╔═██╗░██╔══╝░░\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"██║░░██║░░╚██╔╝░╚██╔╝░██║░░██║██║░╚██╗███████╗\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝\n",&buffersize);
	sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
}