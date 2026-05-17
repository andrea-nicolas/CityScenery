#include<math.h>
#include<GL/glut.h>

float buildingCloudSpeed = 0.0f;
float flyoverCloudSpeed = 0.0f;
float homeCloudSpeed = 0.0f;
float treeShake = 0.0f;
float twinkle = 0.0f;
float containershipSpeed = 0.0f;
float yachtSpeed = 0.0f;
float planeSpeed = 0.0f;
float carSpeed = 0.0f;
float viewX = 0.0f; //controls the "camera"'s x position
int sceneTimer = 0; //internal clock for scene transitions
int sceneState = 0; //controls if we are staying at scene x or transition between scene x and y
int fpsAdjuster = 3000; //internal clocks depend on how fast computer is rendering scenes


// Rain variables
struct RainDrop {
    float x, y, speed, length;
};

float plane1Speed = 0.0f;
float jetSpeed = 0.0f;
const int NUM_DROPS = 200;
RainDrop rainDrops[NUM_DROPS];
bool rainInitialized = false;
bool rainActive = false;
float rainOpacity = 0.0f;




struct buildingsPalette
{
    static void yellow()
    {
        glColor3f(1.0f, 0.945f, 0.502f);
    }

    static void orange()
    {
        glColor3f(1.0f,0.82f,0.502f);
    }

    static void blue()
    {
        glColor3f(0.498f, 0.667f, 0.796f);
    }

    static void purpleLight()
    {
        glColor3f(0.498f, 0.573f, 0.796f);
    }

    static void purpleDark()
    {
        glColor3f(0.518f, 0.498f, 0.796f);
    }
   static void grey()
    {
        glColor3f(0.70f, 0.72f, 0.78f);
    }
    static void darkGrey()
    {
        glColor3f(0.38f, 0.40f, 0.46f);
    }
};

struct flyoverPalette
{
    static void maroon()
    {
        glColor3f(0.486f, 0.267f, 0.31f);
    }

    static void brown()
    {
        glColor3f(0.624f, 0.322f, 0.333f);
    }

    static void burntOrange()
    {
        glColor3f(0.882f, 0.416f, 0.329f);
    }

    static void orange()
    {
        glColor3f(0.953f, 0.62f, 0.376f);
    }

    static void green()
    {
        glColor3f(0.42f, 0.486f, 0.243f);
    }
    static void grey()
    {
        glColor3f(0.65f, 0.60f, 0.58f);
    }
    static void darkGrey()
    {
        glColor3f(0.35f, 0.32f, 0.30f);
    }
};

struct bridgePalette
{
    static void deepBlue(float alpha = 1.0f)
    {
        glColor4f(0.239f, 0.306f, 0.478f, alpha);
    }
    static void blue(float alpha = 1.0f)
    {
        glColor4f(0.333f, 0.431f, 0.678f, alpha);
    }
    static void burntOrange(float alpha = 1.0f)
    {
        glColor4f(0.769f, 0.376f, 0.227f, alpha);
    }
    static void orange(float alpha = 1.0f)
    {
        glColor4f(0.831f, 0.510f, 0.227f, alpha);
    }
    static void grey(float alpha = 1.0f)
    {
        glColor4f(0.290f, 0.369f, 0.420f, alpha);
    }
    static void darkGrey(float alpha = 1.0f)
    {
        glColor4f(0.165f, 0.220f, 0.251f, alpha);
    }
    static void yellow(float alpha = 1.0f)
    {
        glColor4f(0.769f, 0.659f, 0.196f, alpha);
    }
};

struct homePalette
{
    static void navy()
    {
        glColor3f(0.051f, 0.043f, 0.38f);
    }

    static void blue()
    {
        glColor3f(0.161f, 0.275f, 0.412f);
    }

    static void wallsBrown()
    {
        glColor3f(0.42, 0.369, 0.322);
    }

    static void yellow()
    {
        glColor3f(0.894f, 0.827f, 0.161f);
    }

    static void green()
    {
        glColor3f(0.231, 0.478, 0.318);
    }

    static void green2()
    {
       glColor3f(0.176, 0.369, 0.243);
    }

    static void grey()
    {
        glColor3f(0.271, 0.357, 0.42);
    }

    static void darkGrey()
    {
        glColor3f(0.243, 0.318, 0.322);
    }
    static void treeBrown()
    {
        glColor3f(0.341, 0.255, 0.22);
    }
    static void teal()
    {
        glColor3f(0.267, 0.502, 0.51);
    }
};

void idle()
{
    carSpeed = viewX; //carSpeed is tied to camera position

    sceneTimer++;

    if (sceneState == 0) //stay at scene 1
    {
        viewX = 0.0f; //camera is not moving

         if (sceneTimer >= fpsAdjuster / 2)
        {
            rainActive = true;

            if (rainOpacity < 1.0f)
            {
                rainOpacity += 0.0003f;
                if (rainOpacity > 1.0f) rainOpacity = 1.0f;
            }
        }

        if (sceneTimer >= fpsAdjuster) //after 3000 frames, change scenes
        {
            sceneTimer = 0;
            sceneState = 1;
        }
    }
    else if (sceneState == 1) // go to scene 2
    {
        viewX += 0.5f; //camera moves

        if (rainOpacity > 0.0f)
        {
            rainOpacity -= 0.0005f;
            if (rainOpacity < 0.0f) rainOpacity = 0.0f;
        }

        if (viewX >= 900)
        {
            viewX = 900;
            sceneTimer = 0;
            sceneState = 2;
            rainActive = false;
        }
    }
    else if (sceneState == 2) //stay at scene 2
    {
        viewX = 900.0f;
        if (sceneTimer >= fpsAdjuster)
        {
            sceneTimer = 0;
            sceneState = 3;
        }
    }
    else if (sceneState == 3) // go to scene 3
    {
        viewX += 0.5f;
        if (viewX >= 1800)
        {
            viewX = 1800;
            sceneTimer = 0;
            sceneState = 4;
        }
    }
    else if (sceneState == 4) // stay at scene 3
    {
        viewX = 1800.0f;
        if (sceneTimer >= fpsAdjuster)
        {
            sceneTimer = 0;
            sceneState = 5;
        }
    }
    else if (sceneState == 5) // go to scene 4
    {
        viewX += 0.5f;
        if (viewX >= 2700)
        {
                viewX = 2700;
                sceneTimer = 0;
                sceneState = 6;
        }
    }
    else if (sceneState == 6) //stay at scene 4
    {
        viewX = 2700.0f;
        if (sceneTimer >= fpsAdjuster) //reset all the scenes, along with their object position
        {
            buildingCloudSpeed = 0.0f;
            flyoverCloudSpeed = 0.0f;
            homeCloudSpeed = 0.0f;
            treeShake = 0.0f;
            twinkle = 0.0f;
            containershipSpeed = 0.0f;
            yachtSpeed = 0.0f;
            carSpeed = -500.0f;
            planeSpeed = 0.0f;
            viewX = 0.0f;
            sceneTimer = 0;
            sceneState = 0;
            fpsAdjuster = 6000;

            plane1Speed        = -400.0f;
            jetSpeed           = -200.0f;
            rainActive         = false;
            rainOpacity        = 0.0f;
            rainInitialized    = false;
        }
    }

    plane1Speed += 0.08f;

    if(sceneState == 2 || sceneState == 3)
    {
        jetSpeed += 0.2f;

        if(jetSpeed > 900)
        {
            jetSpeed = -900;
        }
    }

    if(plane1Speed > 1200)
    {
        plane1Speed = -400;
    }

    glutPostRedisplay();
}

float getCarY(float x)
{
    if (x >= 900 && x <= 1000) // move UP at flyover ramp
    {
        return (x - 900);
        //car moves up one unit for each increment in x
        // aka if the camera is at x = 900, car is at 900-900=0 -> same y position
        //     if the camera is at x = 901, car is at 901-900=0 -> move up 1 unit
    }
    else if (x > 1000 && x <= 2600)
    {
        return 100.0f;
        //stay at UP position for flyover and bridge
    }
    else if (x > 2600 && x <= 2700)  // move DOWN at bridge ramp
    {
        return 100.0f - (x - 2600);
        //reverse logic
    }
    else
    {
        return 0.0f;
        //stay at original DOWN y position for other scenes
    }
}

void initRain()
{
    srand(42);
    for (int i = 0; i < NUM_DROPS; i++)
    {
        rainDrops[i].x      = (float)(rand() % 900);
        rainDrops[i].y      = (float)(rand() % 600);
        rainDrops[i].speed  = 1.0f + (rand() % 15) * 0.1f;
        rainDrops[i].length = 8.0f + (rand() % 12);
    }
    rainInitialized = true;
}

void updateAndDrawRain()
{
    if (!rainInitialized) initRain();

    for (int i = 0; i < NUM_DROPS; i++)
    {
        rainDrops[i].y -= rainDrops[i].speed * rainOpacity;

        if (rainDrops[i].y < -rainDrops[i].length)
        {
            rainDrops[i].y = 620.0f;
            rainDrops[i].x = (float)(rand() % 900);
        }
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
    for (int i = 0; i < NUM_DROPS; i++)
    {
        float alpha = (0.4f + (rainDrops[i].speed - 1.0f) / 10.0f) * rainOpacity;
        glColor4f(0.6f, 0.75f, 0.95f, alpha);
        glVertex2f(rainDrops[i].x, rainDrops[i].y);
        glColor4f(0.7f, 0.85f, 1.0f, alpha + 0.2f * rainOpacity);
        glVertex2f(rainDrops[i].x - 1.5f,
                   rainDrops[i].y - rainDrops[i].length);
    }
    glEnd();

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_DROPS; i += 5)
    {
        if (rainDrops[i].y < 115.0f && rainDrops[i].y > 95.0f)
        {
            glColor4f(0.7f, 0.85f, 1.0f, 0.5f * rainOpacity);
            glVertex2f(rainDrops[i].x - 3, 110.0f);
            glVertex2f(rainDrops[i].x + 3, 110.0f);
        }
    }
    glEnd();
}

void drawCircle(int xCenter, int yCenter, int radius, float r, float g, float b,float a)
{
    const int segments = 100;
    const float PI = 3.14159265358979f;

    glBegin(GL_POLYGON);
    glColor4f(r,g,b,a);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = xCenter + radius * cosf(angle);
        float y = yCenter + radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCar()
{
    glPushMatrix();
    glTranslatef(carSpeed+100, getCarY(carSpeed +475), 0);
    //350 tuned to y to adjust when the car starts ramping up / down
    //INCREASE to make it earlier
    //DECREASE to make it later

    //100 tuned to x to put it in the center of the screen

    //------------------------------------------------------------------------
    //CAR
    glBegin(GL_POLYGON); //body
    buildingsPalette::orange();
    glVertex2i(270,70);
    glVertex2i(270,92);
    glVertex2i(304,92);
    glVertex2i(318,110);
    glVertex2i(358,110);
    glVertex2i(370,92);
    glVertex2i(406,92);
    glVertex2i(406,70);
    glEnd();

    buildingsPalette::blue();
    glBegin(GL_QUADS); //back window
    glVertex2i(308,92);
    glVertex2i(320,106);
    glVertex2i(334,106);
    glVertex2i(334,92);

    //front window
    glVertex2i(342,106);
    glVertex2i(354,106);
    glVertex2i(362,92);
    glVertex2i(342,92);
    glEnd();

    //car details
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    glVertex2i(338,110); //middle line
    glVertex2i(338,70);

    glVertex2i(324,88); //back door handle
    glVertex2i(334,88);

    glVertex2i(342,88); //front door handle
    glVertex2i(350,88);

    glEnd();

    glBegin(GL_QUADS); //back light
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2i(270,85);
    glVertex2i(270,92);
    glVertex2i(280,92);
    glVertex2i(280,85);

    //front light
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2i(400,92);
    glVertex2i(406,92);
    glVertex2i(406,88);
    glVertex2i(400,88);

    buildingsPalette::blue();
    //back bumper
    glVertex2i(382,74);
    glVertex2i(408,74);
    glVertex2i(408,68);
    glVertex2i(382,68);

    //back bumper
    glColor3f(0.498f, 0.667f, 0.796f);
    glVertex2i(268,75);
    glVertex2i(290,75);
    glVertex2i(290,68);
    glVertex2i(268,68);
    glEnd();

    drawCircle(300,70,12,0.0f,0.0f,0.0f,1.0f); //back wheel
    drawCircle(370,70,12,0.0f,0.0f,0.0f,1.0f); //front wheel
    glPopMatrix();
}

void displayBuildings()
{
    //SKY
    glBegin(GL_QUADS);

    float r = 1.0f   * (1.0f - rainOpacity) + 0.35f * rainOpacity;
    float g = 0.82f  * (1.0f - rainOpacity) + 0.38f * rainOpacity;
    float b = 0.502f * (1.0f - rainOpacity) + 0.45f * rainOpacity;

    float r2 = 1.0f  * (1.0f - rainOpacity) + 0.22f * rainOpacity;
    float g2 = 0.553f* (1.0f - rainOpacity) + 0.24f * rainOpacity;
    float b2 = 0.247f* (1.0f - rainOpacity) + 0.30f * rainOpacity;

    glColor3f(r, g, b);
    glVertex2i(0, 400);
    glVertex2i(900, 400);
    glColor3f(r2, g2, b2);
    glVertex2i(900, 600);
    glVertex2i(0, 600);

    glColor3f(r, g, b);
    glVertex2i(0, 0);
    glVertex2i(0, 400);
    glVertex2i(900, 400);
    glVertex2i(900, 0);
    glEnd();

    //------------------------------------------------------------------------
    //CLOUDS
    glPushMatrix();
    glTranslatef(buildingCloudSpeed, 0, 0);
    drawCircle(141,532,14,1, 0.863, 0.631,1.0); //cloud left
    drawCircle(168,531,14,1, 0.863, 0.631,1.0);
    drawCircle(127,512,14,1, 0.863, 0.631,1.0);
    drawCircle(154,512,14,1, 0.863, 0.631,1.0);
    drawCircle(180,511,14,1, 0.863, 0.631,1.0);

    drawCircle(572,568,20,1, 0.863, 0.631,1.0); //cloud right
    drawCircle(608,568,20,1, 0.863, 0.631,1.0);
    drawCircle(555,545,20,1, 0.863, 0.631,1.0);
    drawCircle(590,545,20,1, 0.863, 0.631,1.0);
    drawCircle(625,545,20,1, 0.863, 0.631,1.0);
    glPopMatrix();

    //------------------------------------------------------------------------
    drawCircle(0,600,120,1.0f, 0.945f, 0.502f,1.0f); //SUN

    //------------------------------------------------------------------------
    //ROAD
    //main
    glBegin(GL_POLYGON);
    glColor3f(0.722f, 0.718f, 0.718f);
    glVertex2i(0,0);
    glVertex2i(0,100);
    glVertex2i(900,100);
    glVertex2i(900,0);
    glEnd();

    //grey parts
    homePalette::grey();
    glBegin(GL_QUADS);
    glVertex2i(0,100);
    glVertex2i(0,110);
    glVertex2i(150,110);
    glVertex2i(150,100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(300,100);
    glVertex2i(300,110);
    glVertex2i(450,110);
    glVertex2i(450,100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(600,100);
    glVertex2i(600,110);
    glVertex2i(750,110);
    glVertex2i(750,100);
    glEnd();

    //yellow parts
    buildingsPalette::yellow();
    glBegin(GL_QUADS);
    glVertex2i(150,100);
    glVertex2i(150,110);
    glVertex2i(300,110);
    glVertex2i(300,100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(450,100);
    glVertex2i(450,110);
    glVertex2i(600,110);
    glVertex2i(600,100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(750,100);
    glVertex2i(750,110);
    glVertex2i(900,110);
    glVertex2i(900,100);
    glEnd();

    //lines
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0; i < 18; i+=2)
    {
        glVertex2i(i*50,50);
        glVertex2i(i*50+50,50);
    }
    glEnd();

    //------------------------------------------------------------------------
    //BUILDINGS
    buildingsPalette::purpleLight();
    glBegin(GL_QUADS); //building 1
    glVertex2i(0,440);   //bigger body
    glVertex2i(180,440);
    glVertex2i(180,110);
    glVertex2i(0,110);

    //body decor lower layer
    glVertex2i(10,440);
    glVertex2i(10,450);
    glVertex2i(170,450);
    glVertex2i(170,440);

    //body decor upper layer
    glVertex2i(20,450);
    glVertex2i(20,460);
    glVertex2i(160,460);
    glVertex2i(160,450);

    //smaller body
    glVertex2i(100,400);
    glVertex2i(200,400);
    glVertex2i(200,110);
    glVertex2i(100,110);

    buildingsPalette::orange();
    //bigger body large window 1
    glVertex2i(20,260);
    glVertex2i(20,420);
    glVertex2i(100,420);
    glVertex2i(100,260);

    //bigger body large window 2
    glVertex2i(100,420);
    glVertex2i(160,420);
    glVertex2i(160,400);
    glVertex2i(100,400);
    glEnd();

    buildingsPalette::yellow();
    glLineWidth(3.0f); //large window yellow details
    glBegin(GL_LINES);
    glVertex2i(20,260);
    glVertex2i(20,420);

    glVertex2i(20,420);
    glVertex2i(160,420);
    glEnd();

    for (int i = 0; i < 14; i+=2)
    {
        buildingsPalette::orange();
        glBegin(GL_QUADS); //smaller body short windows
        glVertex2i(110,260+i*10);
        glVertex2i(110,260+i*10+10);
        glVertex2i(190,260+i*10+10);
        glVertex2i(190,260+i*10);
        glEnd();

        buildingsPalette::yellow();
        glLineWidth(3.0f);
        glBegin(GL_LINES); //window yellow vertical lines
        glVertex2i(110,260+i*10);
        glVertex2i(110,260+i*10+10);

        glVertex2i(110,260+i*10+10); //window yellow horizontal lines
        glVertex2i(190,260+i*10+10);
        glEnd();
    }

    for (int i = 0; i < 14; i+=2)
    {
        buildingsPalette::orange();
        glBegin(GL_QUADS); //smaller body long windows
        glVertex2i(30,120+i*10);
        glVertex2i(30,120+i*10+10);
        glVertex2i(190,120+i*10+10);
        glVertex2i(190,120+i*10);
        glEnd();

        buildingsPalette::yellow();
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2i(30,120+i*10); //window yellow vertical lines
        glVertex2i(30,120+i*10+10);

        glVertex2i(30,120+i*10+10); //window yellow horizontal lines
        glVertex2i(190,120+i*10+10);
        glEnd();
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    homePalette::grey();
    glBegin(GL_QUADS); //background building 1
    glVertex2i(200,300);
    glVertex2i(220,300);
    glVertex2i(220,110);
    glVertex2i(200,110);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    buildingsPalette::blue();
    //building 2
    glVertex2i(220,110); //body
    glVertex2i(220,520);
    glVertex2i(480,520);
    glVertex2i(480,110);

    //body middle
    glVertex2i(300,110);
    glVertex2i(300,550);
    glVertex2i(400,550);
    glVertex2i(400,110);

    buildingsPalette::orange();
    //window left
    glVertex2i(240,500);
    glVertex2i(280,500);
    glVertex2i(280,120);
    glVertex2i(240,120);

    //window middle
    glVertex2i(420,500);
    glVertex2i(460,500);
    glVertex2i(460,120);
    glVertex2i(420,120);

    //window right
    glVertex2i(320,540);
    glVertex2i(380,540);
    glVertex2i(380,120);
    glVertex2i(320,120);
    glEnd();

    buildingsPalette::yellow(); //window details
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2i(240,500); //left window vertical 1
    glVertex2i(240,120);

    glVertex2i(260,500); //left window vertical 2
    glVertex2i(260,120);


    glVertex2i(320,540); //middle window vertical 1
    glVertex2i(320,120);

    glVertex2i(340,540); //middle window vertical 2
    glVertex2i(340,120);

    glVertex2i(360,540); //middle window vertical 3
    glVertex2i(360,120);


    glVertex2i(420,500); //right window vertical 1
    glVertex2i(420,120);

    glVertex2i(440,500); //right window vertical 2
    glVertex2i(440,120);

    for(int i = 1; i <= 19; i++) //left and right window horizontal
    {
        glVertex2i(240,120+i*20);
        glVertex2i(280,120+i*20);

        glVertex2i(420,120+i*20);
        glVertex2i(460,120+i*20);
    }

    for(int i = 0; i < 9; i++) //middle window horizontal
    {
        glVertex2i(320,540-i*50);
        glVertex2i(380,540-i*50);
    }
    glEnd();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    homePalette::grey();
    glBegin(GL_QUADS); //background building 2
    glVertex2i(480,110);
    glVertex2i(480,400);
    glVertex2i(500,400);
    glVertex2i(500,110);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //background building 3
    glVertex2i(560,110);
    glVertex2i(560,440);
    glVertex2i(800,440);
    glVertex2i(800,110);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    buildingsPalette::purpleLight();//building 3
    glVertex2i(500,110); //body
    glVertex2i(500,350);
    glVertex2i(750,350);
    glVertex2i(750,110);

    //body decor left
    glVertex2i(600,350);
    glVertex2i(600,370);
    glVertex2i(680,370);
    glVertex2i(680,350);

    glBegin(GL_QUADS); //body decor right
    glVertex2i(695,350);
    glVertex2i(695,360);
    glVertex2i(740,360);
    glVertex2i(740,350);

    buildingsPalette::orange(); //window
    glVertex2i(510,220);
    glVertex2i(510,340);
    glVertex2i(740,340);
    glVertex2i(740,220);
    glEnd();

    buildingsPalette::yellow(); //window yellow lines
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2i(510,340); //vertical
    glVertex2i(740,340);

    glVertex2i(510,220); //horizontal
    glVertex2i(510,340);
    glEnd();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    buildingsPalette::blue();
    glBegin(GL_QUADS); //building 4
    glVertex2i(770,110); //body lower
    glVertex2i(770,400);
    glVertex2i(900,400);
    glVertex2i(900,110);

    //body upper
    glVertex2i(780,400);
    glVertex2i(780,520);
    glVertex2i(890,520);
    glVertex2i(890,400);

    //body upper top layer 1
    glVertex2i(790,520);
    glVertex2i(790,530);
    glVertex2i(880,530);
    glVertex2i(880,520);

    //body upper top layer 2
    glVertex2i(800,530);
    glVertex2i(800,540);
    glVertex2i(870,540);
    glVertex2i(870,530);

    buildingsPalette::orange(); //body upper rectangle hole
    glVertex2i(800,400);
    glVertex2i(800,475);
    glVertex2i(870,475);
    glVertex2i(870,400);
    glEnd();

    drawCircle(835,475,35,1.0f,0.82f,0.502f,1.0f); //body upper circle hole

    homePalette::grey(); //body upper pole
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex2i(835,540);
    glVertex2i(835,570);
    glEnd();

    for(int i = 0; i < 14; i+=2)
    {
        buildingsPalette::orange();
        glBegin(GL_QUADS); //window
        glVertex2i(780,130+i*20);
        glVertex2i(780,130+i*20+20);
        glVertex2i(890,130+i*20+20);
        glVertex2i(890,130+i*20);
        glEnd();

        buildingsPalette::yellow();
        glLineWidth(3.0f);
        glBegin(GL_LINES);

        glVertex2i(780,130+i*20+20); //horizontal
        glVertex2i(890,130+i*20+20);

        glVertex2i(780,130+i*20); //vertical
        glVertex2i(780,130+i*20+20);
        glEnd();
    }

     homePalette::grey();
    glBegin(GL_QUADS);
    glVertex2i(800, 400);
    glVertex2i(800, 440);
    glVertex2i(850, 440);
    glVertex2i(850, 400);
    glEnd();
     homePalette::grey();
    glBegin(GL_QUADS);
    glVertex2i(800, 400);
    glVertex2i(800, 440);
    glVertex2i(850, 440);
    glVertex2i(850, 400);
    glEnd();

    //------------------------------------------------------------------------
    // PLANE SCENE 1

    glPushMatrix();
    glTranslatef(plane1Speed, 0, 0);

    // plane body
    glColor3f(0.85f,0.85f,0.85f);
    glBegin(GL_QUADS);
    glVertex2i(120,520);
    glVertex2i(200,520);
    glVertex2i(210,535);
    glVertex2i(120,535);
    glEnd();

    // front
    glBegin(GL_TRIANGLES);
    glVertex2i(200,520);
    glVertex2i(225,527);
    glVertex2i(200,535);
    glEnd();

    // back wing
    glBegin(GL_TRIANGLES);
    glVertex2i(145,535);
    glVertex2i(165,560);
    glVertex2i(175,535);
    glEnd();

    // front wing
    glBegin(GL_TRIANGLES);
    glVertex2i(155,520);
    glVertex2i(175,495);
    glVertex2i(185,520);
    glEnd();

    // tail
    glBegin(GL_TRIANGLES);
    glVertex2i(120,535);
    glVertex2i(110,555);
    glVertex2i(130,535);
    glEnd();

    // windows
    glColor3f(0.3f,0.5f,0.8f);
    for(int i=0;i<5;i++)
    {
        drawCircle(140 + i*12,528,2,0.3f,0.5f,0.8f,1.0f);
    }

    glPopMatrix();

    //------------------------------------------------------------------------
    //LAMPOSTS
    for (int i = 0; i < 4; i++)
    {
        glLineWidth(3.0f);
        glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        glVertex2i(150+i*200,110); //lamp post
        glVertex2i(150+i*200,180);
        glEnd();

        drawCircle(150+i*200,180,40,1.0f, 0.945f, 0.502f,0.3f); //light - yellow part
        drawCircle(150+i*200,180,8,1.0f,0.82f,0.502f,0.7f); //light - orange part
    }

    if (rainActive && (sceneState == 0 || sceneState == 1))
    {
        updateAndDrawRain();
    }

    buildingCloudSpeed += 0.008f;
}

void displayFlyover()
{
    //------------------------------------------------------------------------
    //SKY
    glBegin(GL_QUADS);
    flyoverPalette::orange();  // lighter orange at bottom
    glVertex2i(900, 400);
    glVertex2i(1800, 400);
    flyoverPalette::burntOrange();  // darker orange at top
    glVertex2i(1800, 600);
    glVertex2i(900, 600);
    glEnd();

    //------------------------------------------------------------------------
    //SUN
    drawCircle(1313,617,77,0.953f, 0.62f, 0.376f,1.0f);

    //------------------------------------------------------------------------
    //CLOUDS
    glPushMatrix();
    glTranslatef(flyoverCloudSpeed,0,0);
    drawCircle(1092,569,21,1.0f, 0.792f, 0.643f,1.0f); //left
    drawCircle(1118,549,20,1.0f, 0.792f, 0.643f,1.0f);
    drawCircle(1128,578,22,1.0f, 0.792f, 0.643f,1.0f);
    drawCircle(1155,562,20,1.0f, 0.792f, 0.643f,1.0f);

    drawCircle(1554,575,18,1.0f, 0.792f, 0.643f,1.0f); //right
    drawCircle(1585,564,20,1.0f, 0.792f, 0.643f,1.0f);
    drawCircle(1615,580,21,1.0f, 0.792f, 0.643f,1.0f);
    drawCircle(1607,549,16,1.0f, 0.792f, 0.643f,1.0f);
    drawCircle(1634,553,18,1.0f, 0.792f, 0.643f,1.0f);
    glPopMatrix();

    // ================= JET PLANE =================

    if(sceneState == 2 || sceneState == 3)
    {
        glPushMatrix();
        glTranslatef(jetSpeed, 0, 0);

        // ---------------- BODY ----------------
        glColor3f(0.82f,0.82f,0.84f);
        glBegin(GL_QUADS);
        glVertex2i(1050,540);
        glVertex2i(1130,540);
        glVertex2i(1155,553);
        glVertex2i(1050,553);
        glEnd();

        // ---------------- NOSE ----------------
        glBegin(GL_TRIANGLES);
        glVertex2i(1130,540);
        glVertex2i(1170,546);
        glVertex2i(1130,553);
        glEnd();

        // ---------------- TOP WING ----------------
        glBegin(GL_TRIANGLES);
        glVertex2i(1085,553);
        glVertex2i(1110,580);
        glVertex2i(1125,553);
        glEnd();

        // ---------------- LOWER WING ----------------
        glBegin(GL_TRIANGLES);
        glVertex2i(1090,540);
        glVertex2i(1120,515);
        glVertex2i(1130,540);
        glEnd();

        // ---------------- TAIL ----------------
        glBegin(GL_TRIANGLES);
        glVertex2i(1050,553);
        glVertex2i(1035,575);
        glVertex2i(1065,553);
        glEnd();

        // ---------------- WINDOWS ----------------
        glColor3f(0.2f,0.5f,0.9f);
        for(int i=0;i<5;i++)
        {
            drawCircle(1072+i*12,547,2,0.2f,0.5f,0.9f,1.0f);
        }

        // ---------------- ENGINE ----------------
        glColor3f(0.3f,0.3f,0.3f);
        glBegin(GL_QUADS);
        glVertex2i(1075,536);
        glVertex2i(1090,536);
        glVertex2i(1090,542);
        glVertex2i(1075,542);
        glVertex2i(1100,536);
        glVertex2i(1115,536);
        glVertex2i(1115,542);
        glVertex2i(1100,542);
        glEnd();

        // ---------------- FIRE GLOW ----------------
        drawCircle(1045,546,5,1.0f,0.5f,0.1f,0.8f);

        // ---------------- SMOKE ----------------
        drawCircle(1030,546,6,0.8f,0.8f,0.8f,0.3f);
        drawCircle(1015,548,9,0.8f,0.8f,0.8f,0.2f);
        drawCircle(995,550,12,0.8f,0.8f,0.8f,0.15f);

        glPopMatrix();
    }

    //------------------------------------------------------------------------
    //ROAD
    glBegin(GL_QUADS);
    flyoverPalette::grey();
    glVertex2i(900,420);
    glVertex2i(1800,420);
    glColor3f(0.729f, 0.729f, 0.729f);
    glVertex2i(1800,0);
    glVertex2i(900,0);
    glEnd();

    //------------------------------------------------------------------------
    //GRASS AREA
    flyoverPalette::green();

    glBegin(GL_QUADS); //top left side grass area
    glVertex2i(900,300);
    glVertex2i(1200,300);
    glVertex2i(1080,0);
    glVertex2i(900,0);
    glEnd();

    glBegin(GL_QUADS); //top right side grass area
    glVertex2i(1460,400);
    glVertex2i(1800,400);
    glVertex2i(1800,350);
    glVertex2i(1480,350);
    glEnd();

    glBegin(GL_QUADS); //bottom left side grass area
    glVertex2i(900,350);
    glVertex2i(1220,350);
    glVertex2i(1240,400);
    glVertex2i(900,400);
    glEnd();

    glBegin(GL_QUADS); //bottom right side grass area
    glVertex2i(1620,0);
    glVertex2i(1800,0);
    glVertex2i(1800,300);
    glVertex2i(1500,300);
    glEnd();

    flyoverPalette::brown(); //left area: top tree
    glBegin(GL_QUADS); //branch
    glVertex2i(925,245);
    glVertex2i(933,245);
    glVertex2i(933,193);
    glVertex2i(925,185);
    glEnd();
    glPushMatrix();
    glTranslatef(sin(treeShake) * 3, 0, 0);
    drawCircle(930,249,26,0.58f,0.678f,0.325f,1.0f);
    drawCircle(950,263,23,0.58f,0.678f,0.325f,1.0f);
    drawCircle(935,290,20,0.58f,0.678f,0.325f,1.0f);
    glPopMatrix();

    flyoverPalette::brown(); //left area: bottom tree
    glBegin(GL_QUADS); //branch
    glVertex2i(990,0);
    glVertex2i(990,43);
    glVertex2i(1000,43);
    glVertex2i(1000,0);
    glEnd();
    glPushMatrix();
    glTranslatef(sin(treeShake + 1.0f) * 2, 0, 0);
    drawCircle(987,52,15,0.58f,0.678f,0.325f,1.0f);
    drawCircle(995,29,21,0.58f,0.678f,0.325f,1.0f);
    drawCircle(1004,49,11,0.58f,0.678f,0.325f,1.0f);
    drawCircle(996,64,9,0.58f,0.678f,0.325f,1.0f);
    glPopMatrix();

    glColor3f(0.58f,0.678f,0.325f);
    glPushMatrix();
    glTranslatef(sin(treeShake + 2.0f) * 3, 0, 0);
    glBegin(GL_QUADS); //right area: bottom tree (all quads so whole thing shakes)
    glVertex2i(1720,0);
    glVertex2i(1740,20);
    glVertex2i(1780,20);
    glVertex2i(1800,0);
    glVertex2i(1720,20);
    glVertex2i(1740,40);
    glVertex2i(1780,40);
    glVertex2i(1800,20);
    glVertex2i(1720,40);
    glVertex2i(1800,40);
    glVertex2i(1760,80);
    glVertex2i(1760,80);
    glVertex2i(1530,260); //right area: top left tree
    glVertex2i(1540,270);
    glVertex2i(1580,270);
    glVertex2i(1590,260);
    glVertex2i(1530,270);
    glVertex2i(1540,280);
    glVertex2i(1580,280);
    glVertex2i(1590,270);
    glVertex2i(1530,280);
    glVertex2i(1590,280);
    glVertex2i(1560,309);
    glVertex2i(1560,309);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sin(treeShake + 3.0f) * 2, 0, 0);
    drawCircle(1694,290,15,0.58f,0.678f,0.325f,1.0f); //right area: top right tree
    drawCircle(1710,271,16,0.58f,0.678f,0.325f,1.0f);
    drawCircle(1685,268,13,0.58f,0.678f,0.325f,1.0f);
    glPopMatrix();

    //------------------------------------------------------------------------
    //BUILDINGS
    flyoverPalette::maroon();
    glBegin(GL_QUADS);
    glVertex2i(900,360); //building 1
    glVertex2i(900,480); //front part
    glVertex2i(1060,480);
    glVertex2i(1060,360);

    glColor3f(0.6f, 0.353f, 0.4f); //top part
    glVertex2i(900,480);
    glVertex2i(938,510);
    glVertex2i(1085,510);
    glVertex2i(1060,480);

    glColor3f(0.62f, 0.365f, 0.416f); //side part
    glVertex2i(1060,480);
    glVertex2i(1085,510);
    glVertex2i(1085,470);
    glVertex2i(1060,440);

    glColor3f(0.42, 0.478, 0.553); //window
    glVertex2i(920,420);
    glVertex2i(920,460);
    glVertex2i(1040,460);
    glVertex2i(1040,420);

    flyoverPalette::darkGrey(); //door
    glVertex2i(960,360);
    glVertex2i(960,390);
    glVertex2i(990,390);
    glVertex2i(990,360);

    flyoverPalette::brown();
    glVertex2i(1060,360); //building 2
    glVertex2i(1060,440);
    glVertex2i(1210,440);
    glVertex2i(1210,360);

    glColor3f(0.78f, 0.396f, 0.408f); //top part
    glVertex2i(1210,440);
    glVertex2i(1225,470);
    glVertex2i(1085,470);
    glVertex2i(1060,440);

    glColor3f(0.678f, 0.345f, 0.357f); //side part
    glVertex2i(1210,440);
    glVertex2i(1225,470);
    glVertex2i(1225,395);
    glVertex2i(1210,360);

    flyoverPalette::darkGrey(); //door
    glVertex2i(1120,360);
    glVertex2i(1120,380);
    glVertex2i(1140,380);
    glVertex2i(1140,360);

    glColor3f(0.42, 0.478, 0.553); // left window
    glVertex2i(1070,390);
    glVertex2i(1070,430);
    glVertex2i(1110,430);
    glVertex2i(1110,390);

    glVertex2i(1150,390); //right window
    glVertex2i(1150,430);
    glVertex2i(1190,430);
    glVertex2i(1190,390);


    flyoverPalette::maroon();
    glVertex2i(1490,360); //building 3
    glVertex2i(1490,450);
    glVertex2i(1800,450);
    glVertex2i(1800,360);

    glColor3f(0.6f, 0.353f, 0.4f); //top part
    glVertex2i(1490,450);
    glVertex2i(1475,475);
    glVertex2i(1800,475);
    glVertex2i(1800,450);

    glColor3f(0.62f, 0.365f, 0.416f); //side part
    glVertex2i(1475,475);
    glVertex2i(1490,450);
    glVertex2i(1490,360);
    glVertex2i(1475,400);

    flyoverPalette::darkGrey(); //door
    glVertex2i(1540,360);
    glVertex2i(1540,380);
    glVertex2i(1570,380);
    glVertex2i(1570,360);

    glVertex2i(1700,360);
    glVertex2i(1700,380);
    glVertex2i(1730,380);
    glVertex2i(1730,360);

    glColor3f(0.42, 0.478, 0.553); // left window
    glVertex2i(1580,400);
    glVertex2i(1580,440);
    glVertex2i(1680,440);
    glVertex2i(1680,400);

    glVertex2i(1740,400); //right window
    glVertex2i(1740,440);
    glVertex2i(1800,440);
    glVertex2i(1800,400);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    //door lines
    glVertex2i(975,360); //building 1
    glVertex2i(975,390);

    glVertex2i(1130,360); //building 2
    glVertex2i(1130,380);

    glVertex2i(1555,360); //building 3 left door
    glVertex2i(1555,380);

    glVertex2i(1715,360); //building 3 right door
    glVertex2i(1715,380);
    glEnd();

    //window lines
    glColor3f(0.333, 0.384, 0.451);
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glVertex2i(920,420); //building 1
    glVertex2i(1040,420);

    glVertex2i(920,460);
    glVertex2i(920,420);

    glVertex2i(1070,430); //building 2 left window
    glVertex2i(1070,390);

    glVertex2i(1070,390);
    glVertex2i(1110,390);

    glVertex2i(1150,430); //building 2 right window
    glVertex2i(1150,390);

    glVertex2i(1150,390);
    glVertex2i(1190,390);

    glVertex2i(1580,400); //building 3 left window
    glVertex2i(1680,400);

    glVertex2i(1680,440);
    glVertex2i(1680,400);

    glVertex2i(1740,400); //building 3 right window
    glVertex2i(1800,400);

    glEnd();

    //------------------------------------------------------------------------
    //ROAD
    //road lines
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(3.0f); //horizontal line
    glBegin(GL_LINES);
    glVertex2i(900,330);
    glVertex2i(910,330);

    glVertex2i(940,330);
    glVertex2i(980,330);

    glVertex2i(1010,330);
    glVertex2i(1050,330);

    glVertex2i(1080,330);
    glVertex2i(1120,330);

    glVertex2i(1150,330);
    glVertex2i(1180,330);

    glVertex2i(1530,330);
    glVertex2i(1560,330);

    glVertex2i(1590,330);
    glVertex2i(1630,330);

    glVertex2i(1660,330);
    glVertex2i(1700,330);

    glVertex2i(1730,330);
    glVertex2i(1770,330);
    glEnd();

    glLineWidth(15.0f); //vertical line
    glBegin(GL_LINES);
    glVertex2i(1350,50);
    glVertex2i(1350,0);
    glEnd();

    //road borders
    flyoverPalette::darkGrey();
    glBegin(GL_QUADS);
    glVertex2i(1225,420);
    glVertex2i(1225,425);
    glVertex2i(1260,425);
    glVertex2i(1260,420);

    glVertex2i(1315,420);
    glVertex2i(1315,425);
    glVertex2i(1380,425);
    glVertex2i(1380,420);

    glVertex2i(1445,420);
    glVertex2i(1445,425);
    glVertex2i(1475,425);
    glVertex2i(1475,420);

    glColor3f(0.831f, 0.659f, 0.325f);
    glVertex2i(1260,420);
    glVertex2i(1260,425);
    glVertex2i(1315,425);
    glVertex2i(1315,420);

    glVertex2i(1380,420);
    glVertex2i(1380,425);
    glVertex2i(1445,425);
    glVertex2i(1445,420);
    glEnd();

    //------------------------------------------------------------------------
    //PEDESTRIAN CROSSING
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2i(1220,300); //bottom
    glVertex2i(1205,260);

    glVertex2i(1251,300);
    glVertex2i(1240,260);

    glVertex2i(1286,300);
    glVertex2i(1280,260);

    glVertex2i(1316,300);
    glVertex2i(1313,260);

    glVertex2i(1350,300);
    glVertex2i(1350,260);

    glVertex2i(1380,300);
    glVertex2i(1387,260);

    glVertex2i(1408,300);
    glVertex2i(1420,260);

    glVertex2i(1440,300);
    glVertex2i(1457,260);

    glVertex2i(1472,300);
    glVertex2i(1490,260);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2i(1483,342); //right
    glVertex2i(1505,342);

    glVertex2i(1487,333);
    glVertex2i(1508,333);

    glVertex2i(1490,324);
    glVertex2i(1512,325);

    glVertex2i(1494,315);
    glVertex2i(1516,316);

    glVertex2i(1498,306);
    glVertex2i(1518,306);

    glVertex2i(1196, 342);  //left
    glVertex2i(1218, 342);

    glVertex2i(1193, 333);
    glVertex2i(1215, 333);

    glVertex2i(1191, 324);
    glVertex2i(1212, 324);

    glVertex2i(1188, 315);
    glVertex2i(1209, 315);

    glVertex2i(1185, 306);
    glVertex2i(1206, 306);
    glEnd();

    glLineWidth(9.0f);
    glBegin(GL_LINES);
    glVertex2i(1240, 351); //top
    glVertex2i(1250, 370);

    glVertex2i(1275, 352);
    glVertex2i(1283, 371);

    glVertex2i(1304, 351);
    glVertex2i(1307, 370);

    glVertex2i(1327, 351);
    glVertex2i(1329, 370);

    glVertex2i(1350, 350);
    glVertex2i(1350, 370);

    glVertex2i(1377, 370);
    glVertex2i(1380, 350);

    glVertex2i(1404, 371);
    glVertex2i(1410, 350);

    glVertex2i(1432, 371);
    glVertex2i(1440, 350);

    glVertex2i(1455, 371);
    glVertex2i(1465, 350);
    glEnd();

    //------------------------------------------------------------------------
    //TRAFFIC LIGHT
    glColor3f(0.369, 0.369, 0.369); //pole
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2i(1350,330);
    glVertex2i(1350,380);
    glEnd();

    glColor3f(0.2, 0.2, 0.2); //top part
    glBegin(GL_QUADS);
    glVertex2i(1340,380);
    glVertex2i(1340,410);
    glVertex2i(1360,410);
    glVertex2i(1360,380);
    glEnd();

    static int trafficTimer = 0;
    static int trafficState = 0;

    trafficTimer++;
    if (trafficTimer >= fpsAdjuster-2000) //adjust for FPS
    {
        trafficTimer = 0;
        trafficState++;

        if (trafficState >= 3)
        {
            trafficState = 0;
        }
    }

    float redAlpha    = (trafficState == 0) ? 1.0f : 0.2f;
    float yellowAlpha = (trafficState == 1) ? 1.0f : 0.2f;
    float greenAlpha  = (trafficState == 2) ? 1.0f : 0.2f;

    drawCircle(1350,403,3, 1.0f,0.0f,0.0f, redAlpha);
    drawCircle(1350,395,3, 1.0f,1.0f,0.0f, yellowAlpha);
    drawCircle(1350,387,3, 0.0f,1.0f,1.0f, greenAlpha);

    //------------------------------------------------------------------------
    //FLYOVER ROAD
    flyoverPalette::grey();
    glBegin(GL_QUADS);
    glVertex2i(900,0); //bent part
    glVertex2i(900,100);
    glVertex2i(1000,200);
    glVertex2i(1000,100);

    glVertex2i(1000,200); //straight part
    glVertex2i(1800,200);
    glVertex2i(1800,100);
    glVertex2i(1000,100);

    flyoverPalette::darkGrey();
    glVertex2i(900,100);//railings
    glVertex2i(900,140);
    glVertex2i(910,150);
    glVertex2i(910,110);

    glVertex2i(940,140);
    glVertex2i(940,180);
    glVertex2i(950,190);
    glVertex2i(950,150);

    glVertex2i(980,180);
    glVertex2i(980,220);
    glVertex2i(990,230);
    glVertex2i(990,190);

    for (int i = 0; i < 20; i++)
    {
        glVertex2i(1020+i*40,200);
        glVertex2i(1020+i*40,240);
        glVertex2i(1030+i*40,240);
        glVertex2i(1030+i*40,200);
    }

    glVertex2i(900,140);
    glVertex2i(900,160);
    glVertex2i(1000,260);
    glVertex2i(1000,240);

    glVertex2i(1000,240);
    glVertex2i(1000,260);
    glVertex2i(1800,260);
    glVertex2i(1800,240);

    //flyover support structures
    glVertex2i(1000,80); //left top
    glVertex2i(1000,100);
    glVertex2i(1100,100);
    glVertex2i(1100,80);

    glVertex2i(1020,0); //left bottom
    glVertex2i(1020,80);
    glVertex2i(1080,80);
    glVertex2i(1080,0);

    glVertex2i(1600,80); //right top
    glVertex2i(1600,100);
    glVertex2i(1700,100);
    glVertex2i(1700,80);

    glVertex2i(1620,0); //right bottom
    glVertex2i(1620,80);
    glVertex2i(1680,80);
    glVertex2i(1680,0);
    glEnd();

    //road lines
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2i(920,70);
    glVertex2i(960,110);

    for(int i = 0; i<8; i++)
    {
        glVertex2i(1000+i*100,150);
        glVertex2i(1050+i*100,150);
    }
    glEnd();

    flyoverCloudSpeed += 0.008f;
    treeShake+= 0.0004f;
}

void displayBridge()
{
    //------------------------------------------------------------------------
    //SKY
    glBegin(GL_QUADS);
    bridgePalette::deepBlue();
    glVertex2i(1800, 450);
    bridgePalette::burntOrange(); //orange in one corner
    glVertex2i(2700, 450);
    bridgePalette::deepBlue();
    glVertex2i(2700, 600);
    glVertex2i(1800, 600);
    glEnd();

    //------------------------------------------------------------------------
    //SUN
    drawCircle(2700,474,59,0.831f, 0.510f, 0.227f,1.0f);

    //------------------------------------------------------------------------
    //MOON
    drawCircle(1865,559,30,0.894f, 0.827f, 0.161f,1.0f);
    drawCircle(1880,570,32,0.239, 0.306, 0.478,1.0f);

    //------------------------------------------------------------------------
    //PLANE
    glPushMatrix();
    glTranslatef(planeSpeed,0,0);

    glColor3f(0.71, 0.71, 0.71);
    glBegin(GL_TRIANGLES); //back wing
    glVertex2i(2025,580);
    glVertex2i(2035,565);
    glVertex2i(2050,565);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.71, 0.71, 0.71); //body
    glVertex2i(2070,570);
    glVertex2i(2080,560);
    glVertex2i(1995,560);
    glVertex2i(1995,570);

    bridgePalette::grey(); //window
    glVertex2i(2004,566);
    glVertex2i(2004,568);
    glVertex2i(2068,568);
    glVertex2i(2068,566);
    glEnd();

    glColor3f(0.71, 0.71, 0.71);
    glBegin(GL_TRIANGLES);
    glVertex2i(2025,550); //front wing
    glVertex2i(2035,565);
    glVertex2i(2050,565);

    glVertex2i(1995,580); //tail
    glVertex2i(2000,570);
    glVertex2i(1995,570);

    bridgePalette::grey();
    glVertex2i(2070,568); //front window
    glVertex2i(2070,564);
    glVertex2i(2074,564);
    glEnd();

    glPopMatrix();

    //------------------------------------------------------------------------
    //WATER
    glBegin(GL_QUADS);
    bridgePalette::deepBlue();
    glVertex2i(1800, 450);
    bridgePalette::burntOrange();
    glVertex2i(2700, 450);
    bridgePalette::blue();
    glVertex2i(2700, 0);
    glVertex2i(1800, 0);
    glEnd();

    //------------------------------------------------------------------------
    //BUILDINGS
    bridgePalette::darkGrey();
    glBegin(GL_QUADS);

    glVertex2i(1800, 520);
    glVertex2i(1840, 520);
    glVertex2i(1840, 450);
    glVertex2i(1800, 450);

    glVertex2i(1840, 500);
    glVertex2i(1940, 500);
    glVertex2i(1940, 450);
    glVertex2i(1840, 450);

    glVertex2i(1940, 540);
    glVertex2i(1960, 540);
    glVertex2i(1960, 450);
    glVertex2i(1940, 450);

    glVertex2i(1960, 480);
    glVertex2i(1980, 480);
    glVertex2i(1980, 450);
    glVertex2i(1960, 450);

    glVertex2i(1980, 520);
    glVertex2i(2080, 520);
    glVertex2i(2080, 450);
    glVertex2i(1980, 450);

    glVertex2i(2080, 500);
    glVertex2i(2160, 500);
    glVertex2i(2160, 450);
    glVertex2i(2080, 450);

    glVertex2i(2090, 510);
    glVertex2i(2150, 510);
    glVertex2i(2150, 500);
    glVertex2i(2090, 500);

    glVertex2i(2160, 540);
    glVertex2i(2210, 540);
    glVertex2i(2210, 450);
    glVertex2i(2160, 450);

    glVertex2i(2170, 550);
    glVertex2i(2210, 550);
    glVertex2i(2210, 540);
    glVertex2i(2170, 540);

    glVertex2i(2210, 540);
    glVertex2i(2220, 540);
    glVertex2i(2220, 450);
    glVertex2i(2210, 450);

    glVertex2i(2220, 510);
    glVertex2i(2260, 510);
    glVertex2i(2260, 450);
    glVertex2i(2220, 450);

    glVertex2i(2260, 500);
    glVertex2i(2360, 500);
    glVertex2i(2360, 450);
    glVertex2i(2260, 450);

    glVertex2i(2280, 540);
    glVertex2i(2330, 540);
    glVertex2i(2330, 500);
    glVertex2i(2280, 500);

    glVertex2i(2350, 530);
    glVertex2i(2360, 530);
    glVertex2i(2360, 500);
    glVertex2i(2350, 500);

    glVertex2i(2360, 540);
    glVertex2i(2400, 540);
    glVertex2i(2400, 450);
    glVertex2i(2360, 450);

    glVertex2i(2400, 520);
    glVertex2i(2440, 520);
    glVertex2i(2440, 450);
    glVertex2i(2400, 450);

    glVertex2i(2440, 480);
    glVertex2i(2480, 480);
    glVertex2i(2480, 450);
    glVertex2i(2440, 450);

    glVertex2i(2480, 510);
    glVertex2i(2510, 510);
    glVertex2i(2510, 450);
    glVertex2i(2480, 450);

    glVertex2i(2490, 520);
    glVertex2i(2500, 520);
    glVertex2i(2510, 510);
    glVertex2i(2480, 510);

    glVertex2i(2510, 500);
    glVertex2i(2580, 500);
    glVertex2i(2580, 450);
    glVertex2i(2510, 450);

    glVertex2i(2580, 530);
    glVertex2i(2630, 530);
    glVertex2i(2630, 450);
    glVertex2i(2580, 450);

    glVertex2i(2590, 540);
    glVertex2i(2620, 540);
    glVertex2i(2620, 530);
    glVertex2i(2590, 530);

    glVertex2i(2650, 520);
    glVertex2i(2680, 520);
    glVertex2i(2680, 510);
    glVertex2i(2650, 510);

    glVertex2i(2640, 510);
    glVertex2i(2690, 510);
    glVertex2i(2690, 500);
    glVertex2i(2640, 500);

    glVertex2i(2630, 500);
    glVertex2i(2700, 500);
    glVertex2i(2700, 450);
    glVertex2i(2630, 450);
    glEnd();

    //------------------------------------------------------------------------
    //BUILDINGS REFLECTION
    glPushMatrix();
    glTranslatef(0, 450, 0);
    glScalef(1, -1, 1);
    glTranslatef(0, -450, 0);

    bridgePalette::darkGrey(0.4f);
    glBegin(GL_QUADS);

    glVertex2i(1800, 520);
    glVertex2i(1840, 520);
    glVertex2i(1840, 450);
    glVertex2i(1800, 450);

    glVertex2i(1840, 500);
    glVertex2i(1940, 500);
    glVertex2i(1940, 450);
    glVertex2i(1840, 450);

    glVertex2i(1940, 540);
    glVertex2i(1960, 540);
    glVertex2i(1960, 450);
    glVertex2i(1940, 450);

    glVertex2i(1960, 480);
    glVertex2i(1980, 480);
    glVertex2i(1980, 450);
    glVertex2i(1960, 450);

    glVertex2i(1980, 520);
    glVertex2i(2080, 520);
    glVertex2i(2080, 450);
    glVertex2i(1980, 450);

    glVertex2i(2080, 500);
    glVertex2i(2160, 500);
    glVertex2i(2160, 450);
    glVertex2i(2080, 450);

    glVertex2i(2090, 510);
    glVertex2i(2150, 510);
    glVertex2i(2150, 500);
    glVertex2i(2090, 500);

    glVertex2i(2160, 540);
    glVertex2i(2210, 540);
    glVertex2i(2210, 450);
    glVertex2i(2160, 450);

    glVertex2i(2170, 550);
    glVertex2i(2210, 550);
    glVertex2i(2210, 540);
    glVertex2i(2170, 540);

    glVertex2i(2210, 540);
    glVertex2i(2220, 540);
    glVertex2i(2220, 450);
    glVertex2i(2210, 450);

    glVertex2i(2220, 510);
    glVertex2i(2260, 510);
    glVertex2i(2260, 450);
    glVertex2i(2220, 450);

    glVertex2i(2260, 500);
    glVertex2i(2360, 500);
    glVertex2i(2360, 450);
    glVertex2i(2260, 450);

    glVertex2i(2280, 540);
    glVertex2i(2330, 540);
    glVertex2i(2330, 500);
    glVertex2i(2280, 500);

    glVertex2i(2350, 530);
    glVertex2i(2360, 530);
    glVertex2i(2360, 500);
    glVertex2i(2350, 500);

    glVertex2i(2360, 540);
    glVertex2i(2400, 540);
    glVertex2i(2400, 450);
    glVertex2i(2360, 450);

    glVertex2i(2400, 520);
    glVertex2i(2440, 520);
    glVertex2i(2440, 450);
    glVertex2i(2400, 450);

    glVertex2i(2440, 480);
    glVertex2i(2480, 480);
    glVertex2i(2480, 450);
    glVertex2i(2440, 450);

    glVertex2i(2480, 510);
    glVertex2i(2510, 510);
    glVertex2i(2510, 450);
    glVertex2i(2480, 450);

    glVertex2i(2490, 520);
    glVertex2i(2500, 520);
    glVertex2i(2510, 510);
    glVertex2i(2480, 510);

    glVertex2i(2510, 500);
    glVertex2i(2580, 500);
    glVertex2i(2580, 450);
    glVertex2i(2510, 450);

    glVertex2i(2580, 530);
    glVertex2i(2630, 530);
    glVertex2i(2630, 450);
    glVertex2i(2580, 450);

    glVertex2i(2590, 540);
    glVertex2i(2620, 540);
    glVertex2i(2620, 530);
    glVertex2i(2590, 530);

    glVertex2i(2650, 520);
    glVertex2i(2680, 520);
    glVertex2i(2680, 510);
    glVertex2i(2650, 510);

    glVertex2i(2640, 510);
    glVertex2i(2690, 510);
    glVertex2i(2690, 500);
    glVertex2i(2640, 500);

    glVertex2i(2630, 500);
    glVertex2i(2700, 500);
    glVertex2i(2700, 450);
    glVertex2i(2630, 450);
    glEnd();

    glPopMatrix();

    //------------------------------------------------------------------------
    //CONTAINERS
    glPushMatrix();
    glTranslatef(containershipSpeed, 0, 0);

    glBegin(GL_QUADS);
    bridgePalette::blue();
    glVertex2i(1960, 400);
    glVertex2i(2020, 400);
    glVertex2i(2020, 380);
    glVertex2i(1960, 380);

    bridgePalette::orange();
    glVertex2i(2000, 420);
    glVertex2i(2060, 420);
    glVertex2i(2060, 400);
    glVertex2i(2000, 400);

    bridgePalette::yellow();
    glVertex2i(2020, 400);
    glVertex2i(2080, 400);
    glVertex2i(2080, 380);
    glVertex2i(2020, 380);

    bridgePalette::orange();
    glVertex2i(1940, 380);
    glVertex2i(2000, 380);
    glVertex2i(2000, 360);
    glVertex2i(1940, 360);

    bridgePalette::blue();
    glVertex2i(2000, 380);
    glVertex2i(2060, 380);
    glVertex2i(2060, 360);
    glVertex2i(2000, 360);

    bridgePalette::yellow();
    glVertex2i(2060, 380);
    glVertex2i(2120, 380);
    glVertex2i(2120, 360);
    glVertex2i(2060, 360);

    //------------------------------------------------------------------------
    //CONTAINER SHIP
    bridgePalette::burntOrange(); //steam engine
    glVertex2i(1880, 440);
    glVertex2i(1900, 440);
    glVertex2i(1920, 400);
    glVertex2i(1880, 400);

    bridgePalette::grey(); //control room
    glVertex2i(1880, 360);
    glVertex2i(1940, 360);
    glVertex2i(1940, 400);
    glVertex2i(1880, 400);

    bridgePalette::darkGrey(); //body
    glVertex2i(1840,363);
    glVertex2i(1840,380);
    glVertex2i(1900,380);
    glVertex2i(1900,360);

    glVertex2i(1840,363);
    glVertex2i(1860,340);
    glVertex2i(2180,340);
    glVertex2i(2190,360);

    glVertex2i(2120,360);
    glVertex2i(2190,360);
    glVertex2i(2200,380);
    glVertex2i(2140,380);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f); //bars
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(1900,370);
    glVertex2i(2130,370);

    for(int i =0; i<8; i++)
    {
        glVertex2i(1925+i*25,370);
        glVertex2i(1925+i*25,360);
    }
    glEnd();

    //------------------------------------------------------------------------
    //CONTAINER SHIP AND CONTAINERS REFLECTION
    glPushMatrix();
    glTranslatef(0, 340, 0);
    glScalef(1, -1, 1);
    glTranslatef(0, -340, 0);

    glBegin(GL_QUADS);
    bridgePalette::blue(0.4f);
    glVertex2i(1960, 400);
    glVertex2i(2020, 400);
    glVertex2i(2020, 380);
    glVertex2i(1960, 380);
    bridgePalette::orange(0.4f);
    glVertex2i(2000, 420);
    glVertex2i(2060, 420);
    glVertex2i(2060, 400);
    glVertex2i(2000, 400);
    bridgePalette::yellow(0.4f);
    glVertex2i(2020, 400);
    glVertex2i(2080, 400);
    glVertex2i(2080, 380);
    glVertex2i(2020, 380);
    bridgePalette::orange(0.4f);
    glVertex2i(1940, 380);
    glVertex2i(2000, 380);
    glVertex2i(2000, 360);
    glVertex2i(1940, 360);
    bridgePalette::blue(0.4f);
    glVertex2i(2000, 380);
    glVertex2i(2060, 380);
    glVertex2i(2060, 360);
    glVertex2i(2000, 360);
    bridgePalette::yellow(0.4f);
    glVertex2i(2060, 380);
    glVertex2i(2120, 380);
    glVertex2i(2120, 360);
    glVertex2i(2060, 360);
    bridgePalette::burntOrange(0.4f);
    glVertex2i(1880, 440);
    glVertex2i(1900, 440);
    glVertex2i(1920, 400);
    glVertex2i(1880, 400);
    bridgePalette::grey(0.4f);
    glVertex2i(1880, 360);
    glVertex2i(1940, 360);
    glVertex2i(1940, 400);
    glVertex2i(1880, 400);
    bridgePalette::darkGrey(0.4f);
    glVertex2i(1840, 363);
    glVertex2i(1840, 380);
    glVertex2i(1900, 380);
    glVertex2i(1900, 360);
    glVertex2i(1840, 363);
    glVertex2i(1860, 340);
    glVertex2i(2180, 340);
    glVertex2i(2190, 360);
    glVertex2i(2120, 360);
    glVertex2i(2190, 360);
    glVertex2i(2200, 380);
    glVertex2i(2140, 380);
    glEnd();

    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(1900, 370);
    glVertex2i(2130, 370);
    for(int i = 0; i < 8; i++)
    {
        glVertex2i(1925+i*25, 370);
        glVertex2i(1925+i*25, 360);
    }
    glEnd();

    glPopMatrix();

    glPopMatrix();

    //------------------------------------------------------------------------
    //YACHT
    glPushMatrix();
    glTranslatef(-yachtSpeed, 0, 0);

    glBegin(GL_QUADS);
    bridgePalette::grey();
    glVertex2i(2550, 390); //front window
    glVertex2i(2560, 400);
    glVertex2i(2568, 400);
    glVertex2i(2568, 390);

    glVertex2i(2574, 400); //back window
    glVertex2i(2600, 400);
    glVertex2i(2600, 390);
    glVertex2i(2574, 390);

    bridgePalette::blue();
    glVertex2i(2568, 400); //in between windows
    glVertex2i(2574, 400);
    glVertex2i(2574, 390);
    glVertex2i(2568, 390);

    glVertex2i(2525, 375); //body
    glVertex2i(2510, 390);
    glVertex2i(2600, 390);
    glVertex2i(2600, 375);

    glVertex2i(2600, 375); //body back
    glVertex2i(2600, 380);
    glVertex2i(2610, 380);
    glVertex2i(2610, 375);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f); //decor
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(2515,385);
    glVertex2i(2550,385);
    glEnd();

    //reflection
    glPushMatrix();
    glTranslatef(0, 375, 0);
    glScalef(1, -1, 0);
    glTranslatef(0, -375, 0);

    glBegin(GL_QUADS);
    bridgePalette::grey(0.4f);
    glVertex2i(2550, 390); //front window
    glVertex2i(2560, 400);
    glVertex2i(2568, 400);
    glVertex2i(2568, 390);

    glVertex2i(2574, 400); //back window
    glVertex2i(2600, 400);
    glVertex2i(2600, 390);
    glVertex2i(2574, 390);

    bridgePalette::blue(0.4f);
    glVertex2i(2568, 400); //in between windows
    glVertex2i(2574, 400);
    glVertex2i(2574, 390);
    glVertex2i(2568, 390);

    glVertex2i(2525, 375); //body
    glVertex2i(2510, 390);
    glVertex2i(2600, 390);
    glVertex2i(2600, 375);

    glVertex2i(2600, 375); //body back
    glVertex2i(2600, 380);
    glVertex2i(2610, 380);
    glVertex2i(2610, 375);
    glEnd();

    glColor4f(0.0f,0.0f,0.0f,0.4f); //decor
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(2515,385);
    glVertex2i(2550,385);
    glEnd();

    glPopMatrix();

    glPopMatrix();

    //------------------------------------------------------------------------
    //BRIDGE
    glBegin(GL_QUADS);
    bridgePalette::grey(); //main body left
    glVertex2i(1800,100);
    glVertex2i(1800,200);
    glVertex2i(2600,200);
    glVertex2i(2600,100);

    glVertex2i(2600,100); //main body right
    glVertex2i(2600,200);
    glVertex2i(2700,100);
    glVertex2i(2700,0);

    bridgePalette::darkGrey();
    glVertex2i(1850,0); //support structures leftmost
    glVertex2i(1850,100);
    glVertex2i(1900,100);
    glVertex2i(1900,0);

    glVertex2i(2050,0);
    glVertex2i(2050,100);
    glVertex2i(2100,100);
    glVertex2i(2100,0);

    glVertex2i(2350,0);
    glVertex2i(2350,100);
    glVertex2i(2400,100);
    glVertex2i(2400,0);

    glVertex2i(2550,0);
    glVertex2i(2550,100);
    glVertex2i(2600,100);
    glVertex2i(2600,0);

    glVertex2i(1800,260); //railings
    glVertex2i(1800,280);
    glVertex2i(2600,280);
    glVertex2i(2600,260);

    glVertex2i(2600,260);
    glVertex2i(2600,280);
    glVertex2i(2700,180);
    glVertex2i(2700,160);

    glVertex2i(2610,190); //bars
    glVertex2i(2610,250);
    glVertex2i(2620,240);
    glVertex2i(2620,180);

    glVertex2i(2650,150);
    glVertex2i(2650,210);
    glVertex2i(2660,200);
    glVertex2i(2660,140);

    for(int i = 0; i<10; i++)
    {
        glVertex2i(1820+i*80,200);
        glVertex2i(1820+i*80,260);
        glVertex2i(1830+i*80,260);
        glVertex2i(1830+i*80,200);
    }
    glEnd();

    glColor3f(0.0f,0.0f,0.0f); //road lines
    glLineWidth(4.0f);
    glBegin(GL_LINES);

    for(int i = 0; i<14; i+=2)
    {
        glVertex2i(1800+i*55,150);
        glVertex2i(1860+i*55,150);
    }

    glVertex2i(2570,150);
    glVertex2i(2600,150);

    glVertex2i(2600,150);
    glVertex2i(2620,130);

    glVertex2i(2650,100);
    glVertex2i(2680,70);
    glEnd();

    yachtSpeed+=0.01f;
    containershipSpeed += 0.008f;
    planeSpeed+=0.009f;
}
void displayHome()
{
    //------------------------------------------------------------------------
    //SKY
    glBegin(GL_QUADS);
    homePalette::blue();  // blue at bottom
    glVertex2i(2700, 400);
    glVertex2i(3600, 400);
    homePalette::navy();  // navy at top
    glVertex2i(3600, 600);
    glVertex2i(2700, 600);

    homePalette::blue();
    glVertex2i(2700, 0);
    glVertex2i(2700, 400);
    glVertex2i(3600, 400);
    glVertex2i(3600, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(homeCloudSpeed,0,0);
    drawCircle(2927,553,11,0.251, 0.427, 0.639,1.0f); //cloud left
    drawCircle(2946,552,12,0.251, 0.427, 0.639,1.0f);
    drawCircle(2965,553,11,0.251, 0.427, 0.639,1.0f);
    drawCircle(2939,568,11,0.251, 0.427, 0.639,1.0f);
    drawCircle(2958,568,10,0.251, 0.427, 0.639,1.0f);

    drawCircle(3463, 529, 9, 0.251, 0.427, 0.639, 1.0f);  //cloud right
    drawCircle(3454, 516, 11, 0.251, 0.427, 0.639, 1.0f);
    drawCircle(3470, 516, 11, 0.251, 0.427, 0.639, 1.0f);
    drawCircle(3479, 528, 9, 0.251, 0.427, 0.639, 1.0f);
    drawCircle(3487, 515, 10, 0.251, 0.427, 0.639, 1.0f);
    glPopMatrix();

    drawCircle(3331,548,47,0.894f, 0.827f, 0.161f,1.0f); //moon
    drawCircle(3349,563,47,0.051f, 0.043f, 0.38f,1.0f);

    drawCircle(3563, 575, 2, 1,1,1,1.0f); //stars
    drawCircle(3563, 575, 7 + sin(twinkle) * 3, 1,1,1,0.1f);

    drawCircle(3438, 470, 4, 1,1,1,1.0f);
    drawCircle(3438, 470, 12 + sin(twinkle + 0.5f) * 4, 1,1,1,0.1f);

    drawCircle(3236, 548, 1, 1,1,1,1.0f);
    drawCircle(3236, 548, 8 + sin(twinkle + 1.0f) * 3, 1,1,1,0.08f);

    drawCircle(3186, 540, 2, 1,1,1,1.0f);
    drawCircle(3186, 540, 9 + sin(twinkle + 1.5f) * 3, 1,1,1,0.12f);

    drawCircle(3033, 582, 3, 1,1,1,1.0f);
    drawCircle(3033, 582, 10 + sin(twinkle + 2.0f) * 4, 1,1,1,0.09f);

    drawCircle(2976, 478, 4, 1,1,1,1.0f);
    drawCircle(2976, 478, 13 + sin(twinkle + 2.5f) * 5, 1,1,1,0.11f);

    drawCircle(2896, 486, 3, 1,1,1,1.0f);
    drawCircle(2896, 486, 8 + sin(twinkle + 3.0f) * 3, 1,1,1,0.07f);

    drawCircle(2783, 581, 2, 1,1,1,1.0f);
    drawCircle(2783, 581, 6 + sin(twinkle + 3.5f) * 2, 1,1,1,0.1f);

    //------------------------------------------------------------------------
    //GRASS AREA
    glColor3f(0.118, 0.239, 0.184);
    glBegin(GL_QUADS); //grass
    glVertex2i(2700,110);
    glVertex2i(2700,300);
    glVertex2i(3600,300);
    glVertex2i(3600,110);

    homePalette::grey(); //road to house
    glVertex2i(3050,110);
    glVertex2i(3300,110);
    homePalette::darkGrey();
    glVertex2i(3200,200);
    glVertex2i(3150,200);

    //------------------------------------------------------------------------
    //ROAD
    homePalette::grey();
    glVertex2i(2700,0); //main part
    glVertex2i(2700,100);
    glVertex2i(3600,100);
    glVertex2i(3600,0);

    for(int i = 0; i<7; i++) //grey and yellow borders
    {
        if ( i%2 == 0)
        {
            homePalette::yellow();
        }
        else
        {
            homePalette::darkGrey();
        }

        glVertex2i(2700+i*130,100);
        glVertex2i(2700+i*130,110);
        glVertex2i(2830+i*130,110);
        glVertex2i(2830+i*130,100);
    }
    glEnd();

    //------------------------------------------------------------------------
    //TREES AND BUSHES
    homePalette::treeBrown();
    glBegin(GL_QUADS);

    glVertex2i(2760,110); //left tree trunk
    glVertex2i(2760,320);
    glVertex2i(2780,320);
    glVertex2i(2780,110);

    glVertex2i(3500,110); //right tree trunk
    glVertex2i(3500,280);
    glVertex2i(3520,280);
    glVertex2i(3520,110);
    glEnd();

    glPushMatrix();
    glTranslatef(sin(treeShake) * 5, 0, 0);
    drawCircle(2800,428,96,0.231, 0.478, 0.318,1.0f);
    glPopMatrix();
    drawCircle(2770,336,60,0.231, 0.478, 0.318,1.0f);
    drawCircle(2840,306,53,0.231, 0.478, 0.318,1.0f);

    // right tree leaves
    glPushMatrix();
    glTranslatef(sin(treeShake) * 5, 0, 0);
    drawCircle(3478,270,47,0.231, 0.478, 0.318,1.0f);
    drawCircle(3531,326,78,0.231, 0.478, 0.318,1.0f);
    glPopMatrix();
    drawCircle(3536,237,46,0.231, 0.478, 0.318,1.0f);

    // left bush
    glPushMatrix();
    glTranslatef(sin(treeShake) * 4, 0, 0);
    drawCircle(2828,144,31,0.176, 0.369, 0.243,1.0);
    drawCircle(2876,141,29,0.176, 0.369, 0.243,1.0);
    drawCircle(2895,173,28,0.176, 0.369, 0.243,1.0);
    drawCircle(2917,143,30,0.176, 0.369, 0.243,1.0);
    drawCircle(2963,137,26,0.176, 0.369, 0.243,1.0);
    glPopMatrix();
    drawCircle(2947,173,26,0.176, 0.369, 0.243,1.0);
    drawCircle(2854,172,25,0.176, 0.369, 0.243,1.0);

    // right bush
    glPushMatrix();
    glTranslatef(sin(treeShake) * 4, 0, 0);
    drawCircle(3332, 142, 28, 0.176, 0.369, 0.243, 1.0);
    drawCircle(3353, 176, 25, 0.176, 0.369, 0.243, 1.0);
    drawCircle(3458, 156, 34, 0.176, 0.369, 0.243, 1.0);
    glPopMatrix();
    drawCircle(3377, 144, 28, 0.176, 0.369, 0.243, 1.0);
    drawCircle(3384, 180, 17, 0.176, 0.369, 0.243, 1.0);
    drawCircle(3412, 165, 23, 0.176, 0.369, 0.243, 1.0);
    drawCircle(3423, 133, 23, 0.176, 0.369, 0.243, 1.0);

    //------------------------------------------------------------------------
    //HOUSE
    glBegin(GL_QUADS);
    glColor3f(0.329, 0.29, 0.255); //right body
    glVertex2i(3300,200);
    glVertex2i(3390,200);
    glVertex2i(3390,340);
    glVertex2i(3300,340);

    glColor3f(0.231, 0.208, 0.18); //right body decor
    glVertex2i(3390,200);
    glVertex2i(3390,340);
    glVertex2i(3400,340);
    glVertex2i(3400,200);

    glVertex2i(3300,340); //right body veranda
    glVertex2i(3300,360);
    glVertex2i(3410,360);
    glVertex2i(3410,340);

    glColor3f(0.812, 0.753, 0.145); //right body window
    glVertex2i(3320,200);
    glVertex2i(3320,280);
    glVertex2i(3380,280);
    glVertex2i(3380,200);

    glColor3f(0.329, 0.29, 0.255);
    glVertex2i(2960,200); //left body
    glVertex2i(3000,200);
    glVertex2i(3000,390);
    glVertex2i(2960,390);

    glColor3f(0.231, 0.208, 0.18); //left body decor bottom
    glVertex2i(2955,315);
    glVertex2i(2955,325);
    glVertex2i(3000,325);
    glVertex2i(3000,315);

    glVertex2i(2950,390); //left body decor top
    glVertex2i(2950,400);
    glVertex2i(3000,400);
    glVertex2i(3000,390);

    glColor3f(0.812, 0.753, 0.145); //left body window
    glVertex2i(2970,340);
    glVertex2i(2970,380);
    glVertex2i(3000,380);
    glVertex2i(3000,340);

    homePalette::wallsBrown(); //main body
    glVertex2i(3000,200);
    glVertex2i(3000,440);
    glVertex2i(3300,440);
    glVertex2i(3300,200);

    glColor3f(0.231, 0.208, 0.18); //main body decor middle
    glVertex2i(2990,320);
    glVertex2i(2990,330);
    glVertex2i(3310,330);
    glVertex2i(3310,320);

    glColor3f(0.329, 0.29, 0.255); //main body 2nd floor decor left
    glVertex2i(3060,330);
    glVertex2i(3060,440);
    glVertex2i(3080,440);
    glVertex2i(3080,330);

    glVertex2i(3220,330); //main body 2nd floor decor left
    glVertex2i(3220,440);
    glVertex2i(3240,440);
    glVertex2i(3240,330);

    homePalette::yellow(); //main body 2nd floor window
    glVertex2i(3100,330);
    glVertex2i(3100,420);
    glVertex2i(3200,420);
    glVertex2i(3200,330);

    glVertex2i(3160,240); //main body 1st floor window
    glVertex2i(3160,300);
    glVertex2i(3220,300);
    glVertex2i(3220,240);

    homePalette::teal(); //door
    glVertex2i(3080,200);
    glVertex2i(3080,280);
    glVertex2i(3120,280);
    glVertex2i(3120,200);
    glEnd();

    glBegin(GL_POLYGON); //roof
    glVertex2i(2975,440);
    glVertex2i(3140,535);
    glVertex2i(3160,535);
    glVertex2i(3325,440);
    glVertex2i(3310,440);
    glVertex2i(3155,530);
    glVertex2i(3145,530);
    glVertex2i(2990,440);
    glEnd();

    glColor3f(0.231, 0.208, 0.18); //roof inner
    glBegin(GL_POLYGON);
    glVertex2i(2990,440);
    glVertex2i(3145,530);
    glVertex2i(3155,530);
    glVertex2i(3310,440);
    glEnd();

    drawCircle(3150,490,20,0.267, 0.502, 0.51,1.0f); //roof window
    drawCircle(3150,490,16,0.894f, 0.827f, 0.161f,1.0f);

    homePalette::teal();
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glVertex2i(3150,506); //roof window lines
    glVertex2i(3150,474);

    glVertex2i(3134,490);
    glVertex2i(3166,490);

    glColor3f(0.812, 0.753, 0.145); //2nd floor window line
    glVertex2i(3150,420);
    glVertex2i(3150,330);

    glVertex2i(3190,300); //1st floor window line
    glVertex2i(3190,240);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.231, 0.208, 0.18);
    glVertex2i(3000,200); //front wall left
    glVertex2i(3000,260);
    glVertex2i(3100,260);
    glVertex2i(3100,200);

    glVertex2i(3180,200); //front wall left
    glVertex2i(3180,260);
    glVertex2i(3300,260);
    glVertex2i(3300,200);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glVertex2i(3350,400); //2nd floor veranda railings
    glVertex2i(3350,360);

    glVertex2i(3400,400);
    glVertex2i(3400,360);

    glVertex2i(3300,400);
    glVertex2i(3400,400);

    glVertex2i(3300,390);
    glVertex2i(3400,390);

    glVertex2i(3300,380);
    glVertex2i(3400,380);

    glVertex2i(3300,370);
    glVertex2i(3400,370);

    glVertex2i(3140,240); //gate
    glVertex2i(3140,200);

    glVertex2i(3100,240);
    glVertex2i(3180,240);

    glVertex2i(3100,230);
    glVertex2i(3180,230);

    glVertex2i(3100,220);
    glVertex2i(3180,220);

    glVertex2i(3100,210);
    glVertex2i(3180,210);

    glVertex2i(3300,230); //1st floor veranda railings
    glVertex2i(3400,230);

    glVertex2i(3310,230);
    glVertex2i(3310,200);

    glVertex2i(3320,230);
    glVertex2i(3320,200);

    glVertex2i(3330,230);
    glVertex2i(3330,200);

    glVertex2i(3340,230);
    glVertex2i(3340,200);

    glVertex2i(3350,230);
    glVertex2i(3350,200);

    glVertex2i(3360,230);
    glVertex2i(3360,200);

    glVertex2i(3370,230);
    glVertex2i(3370,200);

    glVertex2i(3380,230);
    glVertex2i(3380,200);

    glVertex2i(3390,230);
    glVertex2i(3390,200);

    glVertex2i(3400,230);
    glVertex2i(3400,200);

    glColor3f(0.761, 0.71, 0.149);
    glVertex2i(3350,280); //1st floor veranda line
    glVertex2i(3350,232);
    glEnd();

    homeCloudSpeed+=0.007f;
    treeShake += 0.003f;
    twinkle += 0.003f;
}

void display()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(viewX, viewX + 900, 0, 600);

    displayBuildings();
    displayFlyover();
    displayBridge();
    displayHome();
    drawCar();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(900,600);
    glutCreateWindow("City Scenery by Group 3");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
