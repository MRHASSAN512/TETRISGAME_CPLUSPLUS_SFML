/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * TIP: After completing your project, you can make changes for aesthetics.
 * */
//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "PF-Project, Fall-2022";

//---Height and Width of the Actual Interactive Game---//
const int M = 20; //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10; //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {
    0
};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2], point_2[4][2];
int unique1[4][2], arryForBomb[4][2], raplicaArrayForBomb[4][2];
//----------------------------------------variables------------------------------//
int offcount = 0, levelog = 1, sco = 0, points = 0, h = 0, nolev = 1;
float time2 = 0, timethreshold = 0, fast = 0.3;
bool r = 0, p = 0;
//---Check Uncertain Conditions---//
bool anamoly() {
    for (int i = 0; i < 4; i++)
        if (point_1[i][0] < 0 || point_1[i][0] >= N || point_1[i][1] >= M)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
        return 0;
    return 1;
};
//----------------------------------------------------new anamoly for shadow and bomb function---------------------------------//
bool anamolyshadow() {
    for (int i = 0; i < 4; i++)
        if (unique1[i][0] < 0 || arryForBomb[i][0] < 0 || unique1[i][0] >= N || arryForBomb[i][0] >= N || unique1[i][1] >= M || arryForBomb[i][1] >= M)
            return 0;
        else if (gameGrid[unique1[i][1]][unique1[i][0]] || gameGrid[arryForBomb[i][1]][arryForBomb[i][0]])
        return 0;
    return 1;
};
