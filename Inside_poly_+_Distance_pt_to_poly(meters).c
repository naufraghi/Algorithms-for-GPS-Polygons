#include <stdio.h>
#include <math.h>
int pnpoly(int nvert, long double *vertx, long double *verty,long double testx, long double testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;  
  }
  return c;
}

void latLongToCartesian(long double lat, long double lon, long double *x, long double *y) {
    const long double earthRadius = 6371000.0;
    lat = lat * M_PI / 180.0;
    lon = lon * M_PI / 180.0;
    *x = earthRadius * cos(lat) * cos(lon);
    *y = earthRadius * cos(lat) * sin(lon);
    //*z = earthRadius * sin(lat);
}


long double shortestDistanceToPolygon(int nvert, long double *vertx, long double *verty, long double testx, long double testy) {
    long double minDistance = 99999999; //initialize minDistance to a large number
    for (int i = 0, j = nvert-1; i < nvert; j = i++) {
        //calculate line segment defined by vertices i and j
        long double lineStartx = vertx[i];
        long double lineStarty = verty[i];
        long double lineEndx = vertx[j];
        long double lineEndy = verty[j];
        long double lineVectorx = lineEndx - lineStartx;
        long double lineVectory = lineEndy - lineStarty;
        long double pointVectorx = testx - lineStartx;
        long double pointVectory = testy - lineStarty;
        long double lineLength = sqrt(lineVectorx * lineVectorx + lineVectory * lineVectory);
        long double projectionLength = (pointVectorx * lineVectorx + pointVectory * lineVectory) / lineLength;
        //check if point is outside line segment
        if (projectionLength < 0) {
            long double distance = sqrt((testx - lineStartx) * (testx - lineStartx) + (testy - lineStarty) * (testy - lineStarty));
            minDistance = fmin(minDistance, distance);
        }
        else if (projectionLength > lineLength) {
            long double distance = sqrt((testx - lineEndx) * (testx - lineEndx) + (testy - lineEndy) * (testy - lineEndy));
            minDistance = fmin(minDistance, distance);
        }
        else {
            //calculate distance from point to line
            long double perpendicularx = lineStartx + projectionLength * lineVectorx / lineLength;
            long double perpendulary = lineStarty + projectionLength * lineVectory / lineLength;
            long double distance = sqrt((testx - perpendicularx) * (testx - perpendicularx) + (testy - perpendulary) * (testy - perpendulary));
            minDistance = fmin(minDistance, distance);
        }
    }
    return minDistance;
}


int main() {
    // Write C++ code here
    //std::cout << "Hello world!"<<endl;
    long double point[2] = {-72.2882713, 42.9224518};
    int nvert = 6 ;
    long double vertx[6];
    long double verty[6];
    long double verts[6][2] = {
    {-72.2909488, 42.9226375},
    {-72.2908415, 42.9225963},
    {-72.2907637, 42.9225747},
    {-72.2907074, 42.9226395},
    {-72.2908093, 42.9226768},
    {-72.2909488, 42.9226375}   
    };
    long double verts_cart[6][2];

    long double vertx_cart[6];
    long double verty_cart[6];

    printf("Converting from Lat/long to cartesian coordinates\n");
    for (int i = 0; i<5 ; i++)
    {
        vertx[i] = verts[i][0];
        verty[i] = verts[i][1];
        latLongToCartesian(vertx[i],verty[i],&verts_cart[i][0],&verts_cart[i][1]);
        vertx_cart[i] = verts_cart[i][0];
        verty_cart[i] = verts_cart[i][1];
        
        printf("(%Lf,%Lf) = (%Lf,%Lf)\n",vertx[i],verty[i],verts_cart[i][0],verts_cart[i][1]);
    }
    long double point_cart[2];
    printf("\nOur coordinate:");
    latLongToCartesian(point[0],point[1],&point_cart[0],&point_cart[1]);
    printf("(%Lf,%Lf) = (%Lf,%Lf)\n",point[0],point[1],point_cart[0],point_cart[1]);



    


    int output ;
    output = pnpoly(nvert,vertx,verty,point[0],point[1]);
    long double dist;
    if (output == 0)
    {
        printf("Point lies outside\n");
        dist = shortestDistanceToPolygon(nvert,vertx_cart,verty_cart,point_cart[0],point_cart[1]);
        printf("Distance of point to polygon: %Lf\n",dist);
    }
    else
        printf("Point lies inside\n");

    return 0;
}

