#include "decoder.h"
#include "queue.h"
#include "stack.h"
#include <vector>
#include <algorithm>

using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {
    start = s;
    mapImg = tm;
    pair<int,int> trasure_point = findSpot();
    
    
   // a vector that has all the points visited so far to reach that point
    
    vector<vector<bool>> vector_visit(mapImg.height(), vector<bool> (mapImg.width(),false));
    vector<vector<int>> vector_path(mapImg.height(), vector<int> (mapImg.width(),1));
    vector<vector<pair<int,int>>> path_so_far(mapImg.height(),vector<pair<int,int>>(mapImg.height(),make_pair(-1,-1)));
    // vector<vector<vector<pair<int,int>>>> vector_path_so_far(mapImg.height(), vector<vector<pair<int,int>>> (mapImg.width()));
// vector_path_so_far
    Queue<pair<int,int>> traverse_queue; 
    vector_visit[start.second][start.first] = true;
    vector_path[start.second][start.first] = 0;
    // vector<pair<int,int>> path;
    // path.push_back(start); 
    // vector_path_so_far[start.second][start.first] = path;
    traverse_queue.enqueue(start);

    while(!traverse_queue.isEmpty()) {
        pair<int,int> curr = traverse_queue.dequeue();
        int path_length = vector_path[curr.second][curr.first];
        vector<pair<int,int>> p_neighbour_vect = neighbors(curr);
        
        
        for(int i = 0; i <4; i++) {
            pair<int,int> next = p_neighbour_vect[i];
            if (good(vector_visit,vector_path,curr,next)) {
                // cout << "only good" <<endl;
                vector_visit[next.second][next.first] = true;
                int curr_dis = vector_path[curr.second][curr.first];
                vector_path[next.second][next.first] = curr_dis +1;
                path_so_far[next.second][next.first] = curr;

                // vector<pair<int,int>> path = vector_path_so_far[curr.second][curr.first];
                // path.push_back(next); 
                // vector_path_so_far[next.second][next.first] = path; 
                traverse_queue.enqueue(next);
            }
        }
    }
    pathPts.push_back(trasure_point);
    while(trasure_point != start) {
        trasure_point = path_so_far[trasure_point.second][trasure_point.first];
        pathPts.push_back(trasure_point);
    }
    reverse(pathPts.begin(),pathPts.end());
    

    // pathPts = vector_path_so_far[trasure_point.second][trasure_point.first];
}

PNG decoder::renderSolution(){ 
    int path_size = pathPts.size();
    for(int i = 0; i < path_size; i++) {
        pair<int,int> point = pathPts[i];
        RGBAPixel *pixel_curr = mapImg.getPixel(point.first,point.second);
        pixel_curr->r = 255;
        pixel_curr->g = 0;
        pixel_curr->b = 0;
    }
    return mapImg;
}

PNG decoder::renderMaze(){
    vector<vector<bool>> vector_visit(mapImg.height(), vector<bool> (mapImg.width(),false));
    vector<vector<int>> vector_path(mapImg.height(), vector<int> (mapImg.width(),1));

    Queue<pair<int,int>> traverse_queue; 
    vector_visit[start.second][start.first] = true;
    vector_path[start.second][start.first] = 0;

    setGrey(mapImg,start);
    traverse_queue.enqueue(start);

    while(!traverse_queue.isEmpty()) {
        pair<int,int> curr = traverse_queue.dequeue();
        vector<pair<int,int>> p_neighbour_vect = neighbors(curr);
        
        
        for(int i = 0; i <4; i++) {
            pair<int,int> next = p_neighbour_vect[i];
            if (good(vector_visit,vector_path,curr,next)) {
                // cout << "only good" <<endl;
                vector_visit[next.second][next.first] = true;
                int curr_dis = vector_path[curr.second][curr.first];
                vector_path[next.second][next.first] = curr_dis +1;
                setGrey(mapImg,next);
                traverse_queue.enqueue(next);
            }
        }
    }
    for (int x = start.first - 3; x <= start.first + 3; x++) {
		for (int y = start.second - 3; y <=start.second+3; y++) {
			if(x>=0 && x < (int) mapImg.width() && y >=0 && y < (int) mapImg.height()) {
				RGBAPixel *pixel = mapImg.getPixel(x,y);
				pixel->r = 255;
				pixel->g = 0;
				pixel->b = 0;

			}
		}
	}
    return mapImg;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){
   RGBAPixel * pixel = im.getPixel(loc.first,loc.second);
   pixel->r = 2*(pixel->r/4);
   pixel->b = 2*(pixel->b/4);
   pixel->g = 2*(pixel->g/4);
}

pair<int,int> decoder::findSpot(){
    int width = mapImg.width();
    int height = mapImg.height();
    vector<vector<bool>> vector_visit(mapImg.height(), vector<bool> (mapImg.width(),false));
    vector<vector<int>> vector_path(mapImg.height(), vector<int> (mapImg.width(),-1));

    Queue<pair<int,int>> traverse_queue; 
    vector_visit[start.second][start.first] = true;
    vector_path[start.second][start.first] = 0;

    traverse_queue.enqueue(start);
    int maxDistance = -1;
    pair<int,int> treasure;

    while(!traverse_queue.isEmpty()) {
        pair<int,int> curr = traverse_queue.dequeue();
        vector<pair<int,int>> p_neighbour_vect = neighbors(curr);
        
        
        for(int i = 0; i <4; i++) {
            pair<int,int> next = p_neighbour_vect[i];
            if (good(vector_visit,vector_path,curr,next)) {
                // cout << "only good" <<endl;
                vector_visit[next.second][next.first] = true;
                int curr_dis = vector_path[curr.second][curr.first];
                vector_path[next.second][next.first] = curr_dis +1;
                // setGrey(mapImg,next);
                traverse_queue.enqueue(next);
            }
        }
        if(vector_path[curr.second][curr.first] > maxDistance) {
            maxDistance = vector_path[curr.second][curr.second];
            treasure = curr;
        }
    }
    // int maxDistance = 0;
    // pair<int,int> treasure_point = make_pair(0,0);
    //     for(int i = 0; i <mapImg.width(); i++) {
    //     for(int j = 0; j < mapImg.height(); j++) {
    //         int curr_distance = vector_path[i][j];
    //         if (curr_distance > maxDistance) {
    //             maxDistance = curr_distance;
    //             treasure_point = make_pair(i,j);
    //         }
    //     }
    // }
    // might have a problem in height and width in vector_path
    return treasure;
}

int decoder::pathLength(){
    int size_path = pathPts.size();
    pair<int,int> startPoint = pathPts[0];
    pair<int,int> endPoint = pathPts[size_path-1];
    return abs(startPoint.second - endPoint.second) + abs(startPoint.first - endPoint.first);
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){
   if(next.first>=this->mapImg.width() || next.first <0) return false;
   if(next.second>=this->mapImg.height() || next.second <0) return false;
   if(v[next.second][next.first]) return false;
   int maze_value_curr = d[curr.second][curr.first];
   RGBAPixel *pixel_next = mapImg.getPixel(next.first,next.second);
   if(!compare(*pixel_next,maze_value_curr)) return false;
   return true;

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {
    vector<pair<int,int>> neighbors_vect;
    neighbors_vect.push_back(make_pair(curr.first-1,curr.second));
    neighbors_vect.push_back(make_pair(curr.first,curr.second-1));
    neighbors_vect.push_back(make_pair(curr.first+1,curr.second));
    neighbors_vect.push_back(make_pair(curr.first,curr.second+1));
    return neighbors_vect;
}


bool decoder::compare(RGBAPixel p, int d){
   int maze_val = (p.r % 4)*16+(p.g %4)*4+(p.b %4);
   if (maze_val == ((d+1)%64)) {
      return true;
   }
   else {
      return false;
   }
}
