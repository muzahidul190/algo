#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
double calcDist(double,double,double,double);
int main(){

    vector<pair<double,double>> points,centers,orgCntrs;

    int n,k;
    double x,y;

    cout<<"How many points?\t";
    cin>>n;
    int cluster[n] = {0};
    cout<<"\nPlease enter "<<n<<" points with x and y co-ordinate values.";
    cout<<"\nExample: '5 8' is a single point in co-ordinate (x,y).\n";

    for(int i=0;i<n;i++){
        cin>>x>>y;
        points.push_back(make_pair(x,y));
    }
    do{
        cout<<"Enter the value of k.\nIt should be between 2-"<<n<<":\t";
        cin>>k;
    }while(!(k>1 && k<=n));

    vector<vector<int>> groups;

    cout<<"\nEnter co-ordinates of center points\n";

    for(int i=0;i<k;i++){
        cin>>x>>y;
        centers.push_back(make_pair(x,y));
        groups.emplace_back();
    }

    double dist[n+1][k+1];

    for(int i=0;i<centers.size();i++){
        orgCntrs.push_back(centers[i]);
    }

    bool cond = true;
    for(int cont=1;cond;cont++){
            cout<<"\n\t\tStep "<<cont<<"\n\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<k;j++){
                dist[i][j] = calcDist(points[i].first,points[i].second,centers[j].first,centers[j].second);
            }
        }

        cout<<"\nPoints:\n";
        for(int i=0;i<n;i++){
            cout<<i+1<<": ("<<points[i].first<<","<<points[i].second<<")"<<endl;
        }
        cout<<"\nCenters:\n";
        for(int i=0;i<k;i++){
            cout<<i+1<<": ("<<orgCntrs[i].first<<","<<orgCntrs[i].second<<")"<<endl;
        }

        cout<<"\nDistances\nCn:\t";
        for(int i=0;i<k;i++)
            cout<<setw(8)<<i+1<<' ';
        cout<<endl;
        for(int i=0;i<n;i++){
            cout<<i+1<<"\t";
            for(int j=0;j<k;j++){
                cout<<setw(8)<<dist[i][j]<<' ';
            }
            cout<<endl;
        }

        for(int i=0;i<n;i++){
            double sm = dist[i][0];
            int loc = 0;
            for(int j=0;j<k;j++){
                if(dist[i][j] < sm){
                    sm = dist[i][j];
                    loc = j;
                }
            }
            groups[loc].push_back(i);
            cout<<endl<<"Point "<<i+1<<" is pushed at group "<<loc+1<<"\n";
        }
        cout<<"\nGroup Members:\n";
        for(int i=0;i<groups.size();i++){
            cout<<"\nGroup "<<i+1<<":\t";
            for(int j=0;j<groups[i].size();j++){
                cout<<groups[i][j]+1<<' ';
            }
            cout<<endl;
        }

        for(int i=0;i<groups.size();i++){
            double sumx=0,sumy=0;
            for(int j=0;j<groups[i].size();j++){
                sumx += points[groups[i][j]].first;
                sumy += points[groups[i][j]].second;
            }
            if(groups[i].size()==0){
                centers[i].first = 0;
                centers[i].second = 0;
            }else{
                centers[i].first = (sumx/groups[i].size());
                centers[i].second = (sumy/groups[i].size());
            }
            cout<<"\nNew center G"<<i+1<<": ("<<centers[i].first;
            cout<<", "<<centers[i].second<<")\n";
        }

        if(centers == orgCntrs)
            cond = false;


        orgCntrs.clear();
        if(cond){
            for(int i=0;i<centers.size();i++){
                orgCntrs.push_back(centers[i]);
            }
        }

        for(int i=0;i<groups.size();i++){
            groups[i].clear();
        }

    }

    getch();

    return 0;
}


double calcDist(double x1, double y1, double x2, double y2){
    double res = 0;
    double sqx = pow(x1-x2,2);
    double sqy = pow(y1-y2,2);
    return sqrt(sqx+sqy);
}

