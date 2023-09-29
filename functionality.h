/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
#include <SFML/Graphics.hpp>

using namespace sf;
void fallingPiece(float & timer, float & delay, int & colorNum) {

   if (timer > delay) {
      for (int i = 0; i < 4; i++) {
         point_2[i][0] = point_1[i][0];
         point_2[i][1] = point_1[i][1];
         point_1[i][1] += 1; //How much units downward
      }
      if (!anamoly()) {
         for (int i = 0; i < 4; i++)
            gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
         colorNum = 1 + rand() % 7;
         //int n=rand()%7;
         int n = 1;
         //--- Un-Comment this Part When You Make BLOCKS array ---//

         for (int i = 0; i < 4; i++) {
            point_1[i][0] = BLOCKS[n][i] % 2;
            point_1[i][1] = BLOCKS[n][i] / 2;
         }

      }
      timer = 0;
      time2 += delay; //calculating time
   }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
//-----------------------------movementfunctionstart-------------------------//
void movement(int & delta_x) // movement function to move left or right
{
   for (int i = 0; i < 4; i++) {
      point_2[i][0] = point_1[i][0]; //copying array in point_2
      point_2[i][1] = point_1[i][1];
      point_1[i][0] += delta_x; //moving left or right by changing value to +1  or -1 on pressing button
   }

   if (!anamoly()) //checking anamoly so that block does not loose shape
   {
      for (int i = 0; i < 4; i++) {
         point_1[i][0] = point_2[i][0];
         point_1[i][1] = point_2[i][1];
      }
   }
}
//-----------------------------movementfunctionend-------------------------//
//-----------------------------lineclearfunctionstart-------------------------//
void lineclear() {

   h = 0;
   for (int i = (M - 1); i >= 0; i--) //making nested loop to read all grids
   {
      int count = 0;
      for (int j = 0; j < N; j++) {
         if (gameGrid[i][j]) //checking if row is fill or not
         {
            count++; // if fill it will add one
         } else {

            break; // if not then for second loop is break and started again 

         }
      }

      if (count == N) //if count is equal to the value of number of columns
      {
         offcount++;
         h++;
         for (int k = 0; k < N; k++) {
            gameGrid[i][k] = 0; //making row zero

         }
         int m = i;
         while (m > 0) //grid replacing
         {
            for (int n = 0; n < N; n++) {
               gameGrid[m][n] = gameGrid[m - 1][n];
            }

            m--;
         }

      }
   }
   if (h == 1) {
      points = 10;
      sco += points * levelog;
   } else if (h == 2) {
      points = 30;
      sco += points * levelog;
   } else if (h == 3) {
      points = 60;
      sco += points * levelog;
   } else if (h >= 4) {
      points = 100;
      sco += points * levelog;
   }

}
//-----------------------------lineclearfunctionend-------------------------//
//-----------------------------stoppinggamefunctionstart-------------------------//
bool stopfalling() //to stop game
{
   for (int j = 0; j < N; j++) {
      if (gameGrid[1][j] != 0) //checking if grid is filled or not
      {
         return false; //if grid filled return false
      }
   }

   return true; // or return true
}
//-----------------------------stoppinggamefunctionend-------------------------//
//-----------------------------rotationfunctionstart-------------------------//
void rotation(bool & rotate) // rotation function
{
   int temp[4][2]; //initializing temporary array

   if (rotate == true) //checking if rotate button is pressed or not
   {
      for (int i = 0; i < 4; i++) {
         temp[i][1] = point_1[i][1] - point_1[1][1]; //making a center of rotation by copying points in temporary array
         temp[i][0] = point_1[i][0] - point_1[1][0];

         point_1[i][0] = -temp[i][1] + point_1[1][0]; //getting the rotated array
         point_1[i][1] = temp[i][0] + point_1[1][1];
      }

      if (!anamoly()) //applying anamoly so that block does not loose shape on right side.
      {
         for (int i = 0; i < 4; i++) {
            if (point_1[i][0] < 0) {
               for (int i = 0; i < 4; i++) {
                  point_1[i][0] = point_1[i][0] + 1;

               }
            }

         }
      }

      if (!anamoly()) //for left side 
      {
         for (int i = 0; i < 4; i++) {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
         }
      }
   }
}
//-----------------------------rotationfunctionend-------------------------//
//-----------------------------levelfunctionstart-------------------------//
void levelno() // increasing level number
{

   if (time2 >= (timethreshold + 300)) {
      timethreshold += 300;
      levelog++;
   }

}
//-----------------------------levelfunctionend-------------------------//
//-----------------------------spacefeaturefunctionstart-------------------------//
void spacefeature() {
   while (anamoly()) // applying loop till anamoly is correct
   {
      for (int i = 0; i < 4; i++) {
         point_1[i][1] = point_1[i][1] + 1; // adding value in y-coordinate
      }
   }

   while (!anamoly()) // if anamoly is false 
   {
      for (int i = 0; i < 4; i++) {
         point_1[i][1] = point_1[i][1] - 1; //stopping block before going down by doing -1
      }
   }
}
//-----------------------------spacefeaturefunctionend-------------------------//
//-----------------------------bombfunctionstart-------------------------------//
/*void bombBlastingAgent(int& bombBlastingThreshholdScore,int& coloForBomb , bool& bombBlast,float& bombtimer)
{
if (bombtimer>0.3) {
     for(int i=0; i<4 ;i++)
     {
         raplicaArrayForBomb[i][0]=arryForBomb[i][0];
raplicaArrayForBomb[i][1]=arryForBomb[i][1];
         arryForBomb[i][1] += 1;
     
     }
     
     if (!anamolyshadow()) {
      /*   for (int i = 0; i < 4; i++)
            1gameGrid[bomb[i][1]][bomb[i][0]] = colorNum22;
     
     if(arryForBomb[0][0]<=0){
     if(arryForBomb[0][1]>=19){
     bombBlast=0;
     }
     else if(gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]] == coloForBomb){
     if(bombBlast==1){
     for(int i=0;i<M;i++){
     for(int j=0;j<N;j++){
     gameGrid[i][j]=0;
     }
     }}
     bombBlast=0;
     }
     else{
     
     if(bombBlast==1){
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]+1]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]+1]=0;
     
     }
     bombBlast=0;
     }
     }
     else if(arryForBomb[0][0]>=0){
     if(arryForBomb[0][1]>=19){
     bombBlast=0;
     }
     else if(gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]] == coloForBomb){
     if(bombBlast==1){
     for(int i=0;i<M;i++){
     for(int j=0;j<N;j++){
     gameGrid[i][j]=0;
     }
     }}
     bombBlast=0;
     }
     else{
     if(bombBlast==1){
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]+1]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]+1]=0;
     }
     bombBlast=0;
     }
     }
     else{
     if(arryForBomb[0][1]>=19){
     bombBlast=0;
     }
     else if(gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]] == coloForBomb){
     if(bombBlast==1){
     for(int i=0;i<M;i++){
     for(int j=0;j<N;j++){
     gameGrid[i][j]=0;
     }
     }}
     bombBlast=0;
     }
     else{
    if(bombBlast==1){
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]]=0;
     gameGrid[raplicaArrayForBomb[0][1]+1][raplicaArrayForBomb[0][0]+1]=0;
     gameGrid[raplicaArrayForBomb[0][1]+2][raplicaArrayForBomb[0][0]+1]=0;
     }
      bombBlast=0;
     }
     }
       
     
     }
    
   bombtimer=0;
   }
   if(sco>(bombBlastingThreshholdScore+15))
   {
       bombBlast=1;
     coloForBomb=1+rand()%7;
     //colorNum22=3;
   bombBlastingThreshholdScore+=15;
   int n = 10,o=(rand()%9);
   for (int i = 0; i < 4; i++) {
      arryForBomb[i][0] = BLOCKS[n][i] % 2;
      arryForBomb[i][1] = BLOCKS[n][i] / 2;
       arryForBomb[i][0]=arryForBomb[i][0]+o;
   }
   
}
}
*/
//-----------------------------bombfunctionend----------------------------//
//-----------------------------menufunctionstart-------------------------//
void mainmenu() {
   RenderWindow window(VideoMode(350, 350), "Menu");
   while (window.isOpen()) {
      //-----------------------------------SETTING MENU DIPLAY-----------------------//
      sf::Text text, text1, text2;
      sf::Font font;
      font.loadFromFile("/home/mrhassan/Desktop/BS(CS) PF-Project Fall2022/BS(CS) PF-Project Fall2022/Project/Montserrat/static/Montserrat-Bold.ttf");
      text.setFont(font);
      text.setString("Resume(H)");
      text.setPosition(100, 10);
      text.setCharacterSize(25);
      text.setFillColor(sf::Color::Green);

      text1.setFont(font);
      text1.setString("Restart(R)");
      text1.setPosition(100, 40);
      text1.setCharacterSize(25);
      text1.setFillColor(sf::Color::Green);

      text2.setFont(font);
      text2.setString("High Score");
      text2.setPosition(100, 70);
      text2.setCharacterSize(25);
      text2.setFillColor(sf::Color::Green);

      Event e;
      while (window.pollEvent(e)) {
         if (e.type == Event::Closed) //Event is occurring - until the game is in running state
            window.close();
         if (e.type == Event::KeyPressed) //checking key is pressed or not 
         {
            if (e.key.code == Keyboard::H) //if H pressed close window
               window.close();
            else if (e.key.code == Keyboard::R) //if R pressed restart game
            {
               r = 1;
               window.close();
            }

         }
      }

      //----------------Displaying menu items---------------------//
      window.clear(Color::Black);
      window.draw(text);
      window.draw(text1);
      window.draw(text2);
      window.display();
   }
}
//-----------------------------menufunctionend-------------------------//
//-----------------------------restartfunctionstart-------------------------//
void restart(float & fast) //to restart game
{

   if (r) //checking if r is correct or not
   {
      for (int i = 0; i < 20; i++) {
         for (int j = 0; j < 10; j++) {
            gameGrid[i][j] = 0; //making grid zero
         }
      }

      for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 2; j++) {
            point_1[i][j] = 0; //making blocks zero
            point_2[i][j] = 0;
         }
      }

      offcount = 0, levelog = 1, sco = 0, points = 0, time2 = 0, timethreshold = 0, r = 0, h = 0, fast = 0.3; //making all variables zero
   }

}
//-----------------------------restartfunctionend-------------------------//
//-----------------------------scorecounterfunctionstart-------------------------//
/*void scorecounter()
{  
    

     
    
    sco=(points*levelog);
  
   
}*/
//-----------------------------scorecounterfunctionend-------------------------//
//-----------------------------shadowfunctionstart-------------------------//
void shadow() {
   for (int i = 0; i < 4; i++) {

      unique1[i][0] = point_1[i][0]; //coppying arrays in shadow
      unique1[i][1] = point_1[i][1];

   }
   while (anamolyshadow()) // applying loop till anamoly is correct
   {
      for (int i = 0; i < 4; i++) {
         unique1[i][1] = unique1[i][1] + 1; // adding value in y-coordinate
      }
   }

   while (!anamolyshadow()) // if anamoly is false 
   {
      for (int i = 0; i < 4; i++) {
         unique1[i][1] = unique1[i][1] - 1; //stopping block before going down by doing -1
      }
   }

}
//-----------------------------shadowfunctionend-------------------------//
//-----------------------------levelhardfunctionstart-------------------------//
void levelhard(float & delay) {

   if (levelog > nolev) //checking if level in increasing
   {
      fast = fast / 1.5; //decreasing speed of block after level
      nolev++; //adding it maintain conditon
   }

}
//-----------------------------levelhardfunctionend-------------------------//

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
