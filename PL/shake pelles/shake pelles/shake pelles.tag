SQLite format 3   @    p                                                           p -�   � zA�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  C_indexFilenameBrowseCREATE INDEX Filename ON Browse(Filename)4KindexTagBrowseCREATE INDEX Tag ON Browse(Tag)7OindexNameBrowseCREATE INDEX Name ON Browse(Name)��atableBrowseBrowseCREATE TABLE Browse (Kind INTEGER,Name TEXT,Tag TEXT,Filename TEXT,Lineno INTEGER,Text TEXT,Extra INTEGER)   � ��lU?'��������������� �5	Qma5	)regenerateFoodmain.cH'generateSnakemain.cF5	Qmainmain.cEint main(int argc, char *argv[]) {argcmain.cEint arg   _clrscrmain.c
   $'msg1main.cchar msg1[] =   ''start_xmain.cint start_x =   ''start_ymain.cint start_y =   !_textcolormain.c   _gotoxymain.c   printfmain.c   !_textcolormain.c   printfmain.c   &3createNewSnakesHeadmain.c   &3createNewSnakesHeadmain.c   $-removeSnakesTailmain.c   ,+directionmain.c"Dir direction =   .!-new_head_xmain.c#int new_head_x =   .!-new_heaprintfmain.c
printfmain.c	randmain.csystemmain.cprintfmain.ctimemain.c
srandmain.c
setlocalemain.c	5	Qmainmain.cint main(int argc, char *argv[]) {argcmain.cint argc,!'argvmain.cchar *argv[])
   � ��������������������������������������������������� � ��a�%����{_^2
head_x?!_textcolor>drawSnake=
printf<_gotoxy;
printf:_gotoxy9
printf8_gotoxy7
printf6_gotoxy5drawWalls4_gotoxy3drawWalls2drawSnake1drawFood0_clrscr/%redrawScreen.posY� _clrscre� $_clrscrs� _gotoxyl� _gotoxyn@ H_gotoxyx@ <_textcolorO@ _textcolork@ _textcolorp@ _textcolorw@ _textcolorz@ createNewSnakesHead}@ createNewSnakesHeadq 4direction �q %getNewHeadY� head_x^q head_xa� "head_x �� head_y_� head_yb� head_y �  mmain �  cmsg1g� 	msg1t� msg2h� newHeadPosX� newHeadPos �� �new_head_x �� new_head_y �� �printfN9 printfm9 printfo9 printfq9 printfy9 printf{a randS� 	randVa removeSnakesTail �� *scoref�  snakeLengthZ� snakeLength\� s
printf
printf
rand	
system
printftime	srandsetlocalemainargc	argv
   � �����������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\z>>>>>>>>>>>>>>>>>>>              � �  � �  � �  b  �b  �b  �b  �b  �  � �  � �  � �  � �  � �  � ��  �  z  u~� }  k|� {  az  \y  Wx  Rw  Mv  Hu  Ct  >s  9r� q  /p  *o  %n   m  l  k  j  i  h  g  �f  �e  �d! c b  �a  �`+ _  �^  �]: \  �[D Z  �Y  �X  �WX V  �U  �T  �S  �R  �Q  �P{ O  �N  �M  {L  vK  qJ  lI� H  bG  ]F  XE  SD  NC  IB  DA  ?@  :?  5>  0=� <  &;  !:  9  8  7  6  5  4 3   �2   �1   �0   �/   �.% -   �,   �+   �*M )> (   �'   �&   �%   �$W #   �"   �!   �    �   �   �   �   �   �   |   w   r   m   h   c   ^   Y   T�    J   E   @   ;
		
   � ������������������������������������������������������������������ 
 � � � � � � � � �   
main.cN
main.cM
main.cL
main.cK
main.cJ
main.cI
main.cH
main.cG
main.cF
main.cE
main.c   main.c>   main.c?   main.c@   main.cA   main.cB   main.cC   main.cD   main.cE   main.cF   main.cG   main.cH   main.cJ   main.cK   main.cL   main.cM   main.cN   main.cO   main.cQ   main.cR   main.cS   main.cT   main.cU   main.cV   main.cX   main.cY   main.cZ   main.c\   main.c^   main.c_   main.ca   main.cb   main.ce   main.cf   main.cg   main.ch   main.ci   main.cj   main.ck   main.cl   main.cm   main.cn   main.co   main.cp   main.cq   main.cs   main.ct   main.cu   main.cv   main.cw   main.cx   main.cy   main.cz   main.c{   main.c}   main.c   main.c �
main.c
main.c

main.c	
main.c
main.c
main.c
main.c
main.c
main.c
main.c		main.c �  G ��B��v@���P! � � � g G G G�����������  7)regenerateFoodmain.cH'generateSnakemain.cF� 7Qmainmain.cEint main(int argc, char *argv[]) {argcmain.cEint argc,!'argvmain.cEchar *argv[]) %foodmain.cBint food[2];-7snakeArrmain.cAint snakeArr[100][2];<-EMAX_SNAKE_LENGTHmain.c@const int MAX_SNAKE_LENGTH =4%=FIELD_SIZE_Ymain.c=const int FIELD_SIZE_Y =4
%=FIELD_SIZE_Xmain.c<const int FIELD_SIZE_X =D	3OFIELD_BORDER_SYMBOLmain.c;const short FIELD_BORDER_SYMBOL =4#?FOOD_SYMBOLmain.c9const short FOOD_SYMBOL =@/KSNAKE_BODY_SYMBOLmain.c8const short SNAKE_BODY_SYMBOL =@/KSNAKE_HEAD_SYMBOLmain.c7const short SNAKE_HEAD_SYMBOL =F7OSTART_SNAKE_DIRECTIONmain.c6const Dir START_SNAKE_DIRECTION =@1ISTART_SNAKE_LENGTHmain.c5const int START_SNAKE_LENGTH =3!?GAME_SPEEDmain.c4const double GAME_SPEED =0!9gameStatusmain.c3short int gameStatus =   Dirmain.c
� *h h�������3?KWbnz���������� -<KZir{��������)7ESajw����������{!gedirection �	Dir3FIELD_BORDER_SYMBOL	%FIELD_SIZE_X
%FIELD_SIZE_Y#FOOD_SYMBOL!GAME_SPEED-MAX_SNAKE_LENGTH/SNAKE_BODY_SYMBOL/SNAKE_HEAD_SYMBOL7START_SNAKE_DIRECTION1START_SNA� Dir3FIELD_BORDER_SYMBOL	%FIELD_SIZE_X
%FIELD_SIZE_Y#FOOD_SYMBOL!GAME_SPEED-MAX_SNAKE_LENGTH/SNAKE_BODY_SYMBOL/SNAKE_HEAD_SYMBOL7START_SNAKE_DIRECTION1START_SNAKE_LENGTH_clrscr/_clrscre_clrscrs
_getch_gotoxy3_gotoxy5_gotoxy7_gotoxy9_gotoxy;_gotoxyA_gotoxyF_gotoxyL_gotoxyl_gotoxyn_gotoxyx
_kbhit!_textcolor>!_textcolorH!_textcolorM!_textcolorO!_textcolork!_textcolorp!_textcolorw!_textcolorzargcargv	clock&	clock'� createNewSn� 	Dir �3createNewSnakesHead}3createNewSnakesHeaddirection �drawFood0   drawFoodI
Q *9 ������
)2=HES^i9t����
Z7DMV_pd����������������������jt��������������

!new_head_x �
head_xa
head_y@
head_y_
head_yb'increaseSnake'increaseSnake|isEatingisEating`'isHittingTial)isHittingWallshead_y �head_x �t 	isHit	main �!newHeadPos �� drawSnake=drawWalls2� drawWalls4foodgameOver!� gameOverd!gameStatus'generateSnake� generateSnake*
getDir getDir)!getNewHeadY� getNewHead �goal%
head_x?
head_x^
head_xa
head_y@
head_y_
head_yb'increaseSnake� increaseSnake|isEating� isEating`'isHittingTial)isHittingWalls� isHittingWalls]#isMaxLength isMaxLengthckey() 	mainmoveSnake    moveSnake~mseconds#msg1gmsg1tmsg2h%newDirection!newHeadPosX!new_head_x �!new_head_y �posY-
printf6
printf8
printf:
printf<
printfB
printfG
printfN
printfm
� = *5@KValw�����������'2=HS^it�������$/EP[fq|������������������ � � � � � � � � �   
main.cN
main.cM
main.cL
main.cK
main.cJ
main.cI
main.cH
main.cG
main.cF� 
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c	
main.c

main.c
main.c
main.c
main.c
main.c
main.c� main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c
main.c 
main.c!
main.c"
main.c#� main.c$
main.c%
main.c&
main.c'
main.c(� main.c)   main.c*
main.c+
main.c,
main.c-: main.c.
main.c/
main.c0
main.c1
main.c2
main.c3� main.c4
main.c5
main.c6
main.c7
main.c8
main.c9
main.c:
main.c;
main.c<   main.c=
main.c>
main.c?
main.c@
main.cA
main.cB
main.cC
main.cD
main.cE
 9 � 	*5@KVaw���������'2S^it����������$/:E[q|�������� �G� � � � � � � � � � � � � � � � � � � � �  
main.c �main.c �main.c �main.c �main.c �main.c �main.c �main.c �
main.cG
main.cHl main.cI
main.cJ
main.cK
main.cL
main.cM
main.cN
main.cO� main.cP
main.cQ
main.cR
main.cS
main.cT
main.cU
main.cV� main.cW
main.cX
main.cY
main.cZ� main.c[
main.c\ main.c]
main.c^
main.c_= main.c`
main.ca
main.cb� 
main.cmain.c �
main.ce
main.cf
main.cg
main.ch
main.ci
main.cj
main.ck
main.cl
main.cm
main.cn
main.co
main.cp
main.cqP main.cr
main.cs
main.ct
main.cu
main.cv
main.cw
main.cx
main.cy
main.cz
main.c{f main.c|
main.c}� main.c~
main.cmain.c �� main.c �main.c �main.c �main.c �main.c �   main.c �main.c �main.c �main.c �main.c �
� !- LWbmv���#0@P;`jt��������4���-������                                                                                                                                                                                                                                                                                                                                                                                                                                                      victory �-removeSnakesTail �y �x �#snakeLength �
printfq
printfy
printf{randSrandV%redrawScreen� redrawScreen.)regenerateFood)regenerateFood (regenerateFoodP removeSnakesTail[-removeSnakesTail �	scoref	sleep� 
sleep$snakeArr#snakeLengthC#snakeLengthZ#snakeLength\	srandQ	srandTstart_xistart_xustart_yjstart_yvtimeRtimeUvictory"   victoryrxDxJxHeadPos+yEyKyHeadPos,
   I� ����������������������$).38=BGLQV[`ejoty~����������������������������zupkfa\WRMHC>94/*% ����������������������~xrlf`ZTNHB<60*$     � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �~}|{zyxwvtsrqponmlkjihedba_]\[YXWVU	
 !"#$%&()*+./02345689:;<=>?ABCDEFGHIJKMNOPQRT �  P ����L3 ����P+����nT; � � � � m P P P P        O!_textcolormain.c �Nprintfmain.c �M!_textcolormain.c �L_gotoxymain.c �Kymain.c �int y =Jxmain.c �int x =m +/drawFoodmain.c �void drawFood() {H!_textcolormain.c �Gprintfmain.c �F_gotoxymain.c �Eymain.c �int y =Dxmain.c �int x =-C#/snakeLengthmain.c �int snakeLength =Bprintfmain.c �A_gotoxymain.c �#@%head_ymain.c �int head_y =#?%head_xmain.c �int head_x =>!_textcolormain.c �f -1drawSnakemain.c �void drawSnake() {<printfmain.c �;_gotoxymain.c �:printfmain.c �9_gotoxymain.c �8printfmain.c �7_gotoxymain.c �6printfmain.c �5_gotoxymain.c �   -1drawWallsmain.c �void drawWalls() {3_gotoxymain.c �2drawWallsmain.c �1drawSnakemain.c �0drawFoodmain.c � �  P ����L3 ����P+����nT; � � � � m P P P P        O!_textcolormain.c �Nprintfmain.c �M!_textcolormain.c �L_gotoxymain.c �Kymain.c �int y =Jxmain.c �int x =m +/drawFoodmain.c �void drawFood() {H!_textcolormain.c �Gprintfmain.c �F_gotoxymain.c �Eymain.c �int y =Dxmain.c �int x =-C#/snakeLengthmain.c �int snakeLength =Bprintfmain.c �A_gotoxymain.c �#@%head_ymain.c �int head_y =#?%head_xmain.c �int head_x =>!_textcolormain.c �f -1drawSnakemain.c �void drawSnake() {<printfmain.c �;_gotoxymain.c �:printfmain.c �9_gotoxymain.c �8printfmain.c �7_gotoxymain.c �6printfmain.c �5_gotoxymain.c �   -1drawWallsmain.c �void drawWalls() {3_gotoxymain.c �2drawWallsmain.c �1drawSnakemain.c �0drawFoodmain.c �    �  � �'?Vm���;`����/V}����       "h'msg2main.c �char msg2[] ="g'msg1main.c �char msg1[] =!f#scoremain.c �int score =e_clrscrmain.c �l \/gameOvermain.c �vQsrandmain.c �Rtimemain.c �Srandmain.c �Tsrandmain.c �Utimemain.c �Vrandmain.c �,X!/newHeadPosmain.c �int *newHeadPos =Y!getNewHeadmain.c �-Z#/snakeLengthmain.c �int snakeLength =-\#/snakeLengthmain.c �int snakeLength =#^%head_xmain.c �int head_x =#_%head_ymain.c �int head_y =#a%head_xmain.c �int head_x =#b%head_ymain.c �int head_y =e_clrscrmain.c �!f#scoremain.c �int score ="g'msg1main.c �char msg1[] ="h'msg2main.c �char msg2[] =%i'start_xmain.c �int start_x =%j'start_ymain.c �int start_y =k!_textcolormain.c �l_gotoxymain.c �mprintfmain.c �n_gotoxymain.c oprintfmain.c   � ��lF ���/V}����+Pu����'@]x����                /_clrscrmain.c � 3%7redrawScreenmain.c �void redrawS-!posYmain.c �int posY =/_clrscrmain.c �0drawFoodmain.c �1drawSnakemain.c �2drawWallsmain.c �3_gotoxymain.c �5_gotoxymain.c �6printfmain.c �7_gotoxymain.c �8printfmain.c �9_gotoxymain.c �:printfmain.c �;_gotoxymain.c �<printfmain.c �>!#^%head_xmain.c �int head_x =#_%head_ymain.c �int head_y =#a%head_xmain.c �int head_x =#b%head_ymain.c �int head_y =e_cl�ymain.cBint y =�
xmain.cAint x =-�	#/snakeLengthmain.c?int snakeLength =#�%head_ymain.c>int head_y =#�%head_xmain.c=int head_x =3�	'9isHittingTialmain.c<bool isHittingTial() {-�!1newHeadPosmain.c8int newHeadPos[] =+�!-new_head_ymain.c$int new_head_y =                            
   	                V V V V V+05:@FLRO_gotoxymain.c �Nymain.c �int y =Mxmain.c �int x =  +/drawFoodmain.c �void drawFood() {K!_textcolormain.c �Jprintfmain.c �I_gotoxymain.c �Hymain.c �int y =Gxmain.c �int x =-F#/snakeLengthmain.c �int snakeLength =Eprintfmain.c �D_gotoxymain.c �#C%head_ymain.c �int head_y =#B%head_xmain.c �int head_x =A!_textcolormain.c � -1drawSnakemain.c �void drawSnake() {?printfmain.c �>_gotoxymain.c �=printfmain.c �<_gotoxymain.c �;printfmain.c �:_gotoxymain.c �9printfmain.c �8_gotoxymain.c �� -1drawWallsmain.c �void drawWalls() {6_gotoxymain.c �5drawWallsmain.c �4drawSnakemain.c �3drawFoodmain.c �2_clrscrmain.c �   3%7redrawScreenmain.c �void redrawScreen() { p  V ����lT4�����jQ!���x � � � V V V V V                      /_clrscrmain.c � 3%7redrawScreenmain.c �void redrawScreen() {-!posYmain.c �int posY =',)yHeadPosmain.c �int yHeadPos ='+)xHeadPosmain.c �int xHeadPos =� b'9generateSnakemain.c �void generateSnake() {� -9getDirmain.ctDir getDir(long key) {(keymain.ctlong key)'clockmain.cq&clockmain.cp"%)goalmain.cpclock_t goal =   9Ssleepmain.covoid sleep(unsigned int mseconds) {.#9msecondsmain.counsigned int mseconds)"victorymain.cf!gameOvermain.cb moveSnakemain.c\#isMaxLengthmain.cX)regenerateFoodmain.cW'increaseSnakemain.cVisEatingmain.cU'isHittingTialmain.cS)isHittingWallsmain.cS_getchmain.cOgetDirmain.cO_kbhitmain.cN-%/newDirectionmain.cMDir newDirection;sleepmain.cL%redrawScreenmain.cK    �  � �,Pw����$Jp���Lr��� � � b b NE%v'start_ym7�	Ssle+�!-new_head_xmain.c#int new_head_x   8	Qmainmain.cE5�	Qmainmain.cint main(int argc, char *argv[]) {p!_textcolormain.cqprintfmain.cs_clrscrmain.c
"t'msg1main.cchar msg1[] =%u'start_xmain.cint start_x =%v'start_ymain.cint start_y =w!_textcolormain.cx_gotoxymain.cyprintfmain.cz!_textcolormain.c{printfmain.c$}3createNewSnakesHeadmain.c$3createNewSnakesHeadmain.c!� -removeSnakesTailmain.c)�+directionmain.c"Dir direction =+�!-new_head_xmain.c#int new_head_x =+�!-new_head_ymain.c$int new_head_y =-�!1newHeadPosmain.c8int newHeadPos[] =#�%head_xmain.c=int head_x =#�%head_ymain.c>int head_y =-�	#/snakeLengthmain.c?int snakeLength =�
xmain.cAint x =�ymain.cBint y =