#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
double calcDist(double,double,double,double);
struct point{
    double x,y,dist;
    int cat;
};
bool sortpoints(point a, point b){
    return a.dist<b.dist;
}
int main(){

    int n,c;
    double x,y;

    cout<<"How many points?\t";
    cin>>n;
    point points[n+1];
    cout<<"\nHow many categories?\t";
    cin>>c;
    getchar();
    string cats[c+1];
    cout<<"\nEnter categories:\n";
    for(int i=1;i<=c;i++){
        cout<<i<<":\t";
        getline(cin,cats[i-1]);
    }

    cout<<"\nNow enter points with their category.\nExample: '5 3 1' for (x,y) = (5,3) and category = 1.\n";

    for(int i=0;i<n;i++){
        cin>>points[i].x>>points[i].y>>points[i].cat;
    }
    do{

        cout<<"\nEnter the sample point coordinates:\nExample: '4 5' for (x,y) = (4,5)\n";
        cin>>x>>y;

        for(int i=0;i<n;i++)
            points[i].dist = calcDist(x,y,points[i].x,points[i].y);

        cout<<"\n\nThe test points are:\n";
        cout<<"Pn"<<setw(8)<<"X"<<setw(8)<<"Y\t"<<setw(8)<<"\tCategory\n";
        for(int i=0;i<n;i++){
            cout<<i+1<<":"<<setw(8)<<points[i].x<<setw(8)<<points[i].y<<setw(8)<<"\t"<<cats[points[i].cat-1]<<endl;
        }

        cout<<"\n\nThe distances of points from sample point are:\nPn\tDistance\n";
        for(int i=0;i<n;i++){
            cout<<i+1<<":\t"<<points[i].dist<<endl;
        }

        sort(points, points + n, sortpoints);

        //Edit Starts for value k

        int k;
        do{
            cout<<"Enter value of k (1-"<<n<<"):\n";
            cin>>k;
        }while(!(k>0 && k<=n));

        double finx=0,finy=0;

        for(int i=0;i<k;i++){
            finx += points[i].x;
            finy += points[i].y;
        }
        finx /= k;
        finy /= k;

        for(int i=0;i<n;i++)
            points[i].dist = calcDist(finx,finy,points[i].x,points[i].y);



        cout<<"\n\nThe distances of points from average points of k are:\nPn\tDistance\n";
        for(int i=0;i<n;i++){
            cout<<i+1<<":\t"<<points[i].dist<<endl;
        }

        sort(points, points + n, sortpoints);


        //Edit ends for value k



        cout<<"\nThe Category of the sample is:\t"<<cats[points[0].cat-1]<<endl;
    }while(x == y && x == 0);

}


double calcDist(double x1, double y1, double x2, double y2){
    double res = 0;
    double sqx = pow(x1-x2,2);
    double sqy = pow(y1-y2,2);
    return sqrt(sqx+sqy);
}

