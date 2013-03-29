#include <stdio.h>

#include "tasks.h"
#include "cqueue.h"

Task lookLeftTask = { .taskFunction = lookLeft, .executionTime = 4 };
Task lookRightTask = { .taskFunction = lookRight, .executionTime = 2 };
Task lookCenterTask = { .taskFunction = lookCenter, .executionTime = 2 };
Task lookLeftCenterTask = { .taskFunction = lookLeftCenter, .executionTime = 2 };
Task lookRightCenterTask = { .taskFunction = lookRightCenter, .executionTime = 2 };
Task realignCenterTask = { .taskFunction = realignCenter, .executionTime = 4 };
Task captureImgLeftTask = { .taskFunction = captureImgLeft, .executionTime = 1 };
Task captureImgRightTask = { .taskFunction = captureImgRight, .executionTime = 1 };
Task captureImgCenterTask = { .taskFunction = captureImgCenter, .executionTime = 1 };
Task captureImgLeftCenterTask = { .taskFunction = captureImgLeftCenter, .executionTime = 1 };
Task captureImgRightCenterTask = { .taskFunction = captureImgRightCenter, .executionTime = 1 };
Task decipherImgRightCenterTask = { .taskFunction = decipherImgRightCenter, .executionTime = 1 };
Task decipherImgLeftTask = { .taskFunction = decipherImgLeft, .executionTime = 1 };
Task decipherImgRightTask = { .taskFunction = decipherImgRight, .executionTime = 1 };
Task decipherImgCenterTask = { .taskFunction = decipherImgCenter, .executionTime = 1 };
Task decipherImgLeftCenterTask = { .taskFunction = decipherImgLeftCenter, .executionTime = 1 };
Task approachTrackTask = { .taskFunction = approachTrack, .executionTime = 5 };
Task initiateCrossingTask = { .taskFunction = initiateCrossing, .executionTime = 1 };
Task crossTrackTask = { .taskFunction = crossTrack, .executionTime = 3 };
Task avoidRobotTask = { .taskFunction = avoidRobot, .executionTime = 10 };

/* LOOK TASKS */ 
void lookLeft()
{
	//printf("Look Left Task\n");
}

void lookRight()
{
	//printf("Look Right Task\n");
}

void lookCenter()
{
	//printf("Look Center Task\n");
}

void lookLeftCenter()
{
	//printf("Look Left Center Task\n");
}

void lookRightCenter()
{
	//printf("Look Right Center Task\n");
}

/* REALIGN TASKS */

void realignCenter()
{
	//printf("Realign Center Task\n");
}

/* CAPTURE IMG TASKS */

void captureImgLeft()
{
	//printf("Capture Image Left Task\n");
}

void captureImgRight()
{
	//printf("Capture Image Right Task\n");
}

void captureImgCenter()
{
	//printf("Capture Image Center Task\n");
}

void captureImgLeftCenter()
{
	//printf("Capture Image Left Center Task\n");
}

void captureImgRightCenter()
{
	//printf("Capture Image Right Center Task\n");
}

/* DECIPHER IMG TASKS */	
void decipherImgLeft()
{
	//printf("Decipher Image Left Task\n");
}

void decipherImgRight()
{
	//printf("Decipher Image Right Task\n");
}

void decipherImgCenter()
{
	//printf("Decipher Image Center Task\n");
}

void decipherImgLeftCenter()
{
	//printf("Decipher Image Left Center Task\n");
}

void decipherImgRightCenter()
{
	//printf("Decipher Image Right Center Task\n");
}

/* initiate crossing */
void initiateCrossing()
{
    static int debug = 0;
    
    debug++;
    
	//printf("Initiate Crossing Task\n");
    
    /* For testing: Every other hyperperiod either cross or avoid */
    if(debug%2)
    {
        queueInsert(&crossTrackTask,sporadicQ);
    }
    else
    {
        queueInsert(&avoidRobotTask,aperiodicQ);
    }
}

/* SPORADIC TASKS */

void crossTrack()
{
	//printf("Cross Track Task\n");
}

/* APERIODIC TASKS */

void avoidRobot()
{
	//printf("Avoid Robot Task\n");
}

void approachTrack()
{
	//printf("Approach Track Task\n");
}

