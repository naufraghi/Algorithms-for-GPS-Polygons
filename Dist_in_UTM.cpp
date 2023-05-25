
#include <iostream>
#include "UTM.h"
using namespace std;
#include <math.h>
int pnpoly(int nvert, double *vertx, double *verty,double testx, double testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;  
  }
  return c;
}



double shortestDistanceToPolygon(int nvert, double *vertx, double *verty, double testx, double testy) {
    double minDistance = 99999999; //initialize minDistance to a large number
    for (int i = 0, j = nvert-1; i < nvert; j = i++) {
        //calculate line segment defined by vertices i and j
        double lineStartx = vertx[i];
        double lineStarty = verty[i];
        double lineEndx = vertx[j];
        double lineEndy = verty[j];
        double lineVectorx = lineEndx - lineStartx;
        double lineVectory = lineEndy - lineStarty;
        double pointVectorx = testx - lineStartx;
        double pointVectory = testy - lineStarty;
        double lineLength = sqrt(lineVectorx * lineVectorx + lineVectory * lineVectory);
        double projectionLength = (pointVectorx * lineVectorx + pointVectory * lineVectory) / lineLength;
        //check if point is outside line segment
        if (projectionLength < 0) {
            double distance = sqrt((testx - lineStartx) * (testx - lineStartx) + (testy - lineStarty) * (testy - lineStarty));
            minDistance = fmin(minDistance, distance);
        }
        else if (projectionLength > lineLength) {
            double distance = sqrt((testx - lineEndx) * (testx - lineEndx) + (testy - lineEndy) * (testy - lineEndy));
            minDistance = fmin(minDistance, distance);
        }
        else {
            //calculate distance from point to line
            double perpendicularx = lineStartx + projectionLength * lineVectorx / lineLength;
            double perpendulary = lineStarty + projectionLength * lineVectory / lineLength;
            double distance = sqrt((testx - perpendicularx) * (testx - perpendicularx) + (testy - perpendulary) * (testy - perpendulary));
            minDistance = fmin(minDistance, distance);
        }
    }
    return minDistance;
}


int main() {
    // Write C++ code here
    //std::cout << "Hello world!"<<endl;
     double point[2] = {49.87272499030939, 8.650219822192202};
    int nvert = 6 ;
     double vertx[6];
     double verty[6];
     double verts[6][2] = {
		{49.872775121153346, 8.650754922890673},
		{49.87279586493565, 8.650707984232913},
		{49.87276302060957, 8.650650316739092},
		{49.87274400546324, 8.650695914292346},
		{49.87274919141299, 8.650760287308703},
		{49.872775121153346, 8.650754922890673}
    };
     float verts_UTM[6][2];

     double vertx_UTM[6];
     double verty_UTM[6];

    printf("Converting from Lat/long to UTM coordinates\n");
    for (int i = 0; i<5 ; i++)
    {
        vertx[i] = verts[i][0];
        verty[i] = verts[i][1];
        LatLonToUTMXY(vertx[i],verty[i],0,verts_UTM[i][0],verts_UTM[i][1]);
        vertx_UTM[i] = verts_UTM[i][0];
        verty_UTM[i] = verts_UTM[i][1];
        
        printf("(%f,%f) = (%f,%f)\n",vertx[i],verty[i],verts_UTM[i][0],verts_UTM[i][1]);
    }
    float point_utm[2];
    double x_UTM;
    double y_UTM;
    printf("\nOur coordinate:");
    LatLonToUTMXY(point[0],point[1],0,point_utm[0],point_utm[1]);
    x_UTM = point_utm[0];
    y_UTM = point_utm[1];
    printf("(%f,%f) = (%f,%f)\n",point[0],point[1],x_UTM,y_UTM);



    


    int output ;
    output = pnpoly(nvert,vertx,verty,point[0],point[1]);
    double dist;
    if (output == 0)
    {
        printf("Point lies outside\n");
        dist = shortestDistanceToPolygon(nvert,vertx_UTM,verty_UTM,point_utm[0],point_utm[1]);
        printf("Distance of point to polygon: %f\n",dist);
    }
    else
        printf("Point lies inside\n");

    return 0;
}

