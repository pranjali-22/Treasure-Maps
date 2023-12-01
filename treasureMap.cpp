#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
    start = s;
    base = baseim;
    maze = mazeim;
}


void treasureMap::setGrey(PNG & im, pair<int,int> loc){
    RGBAPixel * pixel = im.getPixel(loc.first,loc.second);
    pixel->r = 2*(pixel->r/4);
    pixel->b = 2*(pixel->b/4);
    pixel->g = 2*(pixel->g/4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    int dd = d%64;
    RGBAPixel *pixel = im.getPixel(loc.first,loc.second);
    pixel->r = ((pixel->r) & 0b11111100) |  dd>>4;
    pixel->g = (pixel->g & 0b11111100) |(22 >> 2) & 0b11;
    pixel->b = ((pixel->b) & 0b11111100) | (0b000011 & dd);
}

PNG treasureMap::renderMap(){
    PNG basecpy = base;
    vector<vector<bool>> vector_visit(basecpy.height(), vector<bool> (basecpy.width(),false));
    vector<vector<int>> vector_path(basecpy.height(), vector<int> (basecpy.width(),1));

    Queue<pair<int,int>> traverse_queue; 
    vector_visit[start.second][start.first] = true;
    vector_path[start.second][start.first] = 0;

    setLOB(basecpy,start,0);
    traverse_queue.enqueue(start);

    while(!traverse_queue.isEmpty()) {
        pair<int,int> curr = traverse_queue.dequeue();
        // traverse_queue.dequeue();
        vector<pair<int,int>> p_neighbour_vect = neighbors(curr);
        
        // int neigh_size = p_neighbour_vect.size();
        
        for(int i = 0; i <4; i++) {
            // cout << "reached for loop" <<endl;
            pair<int,int> next = p_neighbour_vect[i];
            if (good(vector_visit,curr,next)) {
                cout << "only good" <<endl;
                vector_visit[next.second][next.first] = true;
                int curr_dis = vector_path[curr.second][curr.first];
                vector_path[next.second][next.first] = curr_dis +1;
                setLOB(basecpy,next,curr_dis+1);
                traverse_queue.enqueue(next);
            }
        }
    }
    return basecpy;
}


PNG treasureMap::renderMaze(){
    PNG basecpy = base;
    vector<vector<bool>> vector_visit(basecpy.height(), vector<bool> (basecpy.width(),false));
    vector<vector<int>> vector_path(basecpy.height(), vector<int> (basecpy.width(),1));

    Queue<pair<int,int>> traverse_queue; 
    vector_visit[start.second][start.first] = true;
    vector_path[start.second][start.first] = 0;

    setGrey(basecpy,start);
    traverse_queue.enqueue(start);

    while(!traverse_queue.isEmpty()) {
        pair<int,int> curr = traverse_queue.dequeue();
        // traverse_queue.dequeue();
        vector<pair<int,int>> p_neighbour_vect = neighbors(curr);
        
        // int neigh_size = p_neighbour_vect.size();
        
        for(int i = 0; i <4; i++) {
            // cout << "reached for loop" <<endl;
            pair<int,int> next = p_neighbour_vect[i];
            if (good(vector_visit,curr,next)) {
                cout << "only good" <<endl;
                vector_visit[next.second][next.first] = true;
                int curr_dis = vector_path[curr.second][curr.first];
                vector_path[next.second][next.first] = curr_dis +1;
                setGrey(basecpy,next);
                traverse_queue.enqueue(next);
            }
        }
    }
	for (int x = start.first - 3; x <= start.first + 3; x++) {
		for (int y = start.second - 3; y <=start.second+3; y++) {
			if(x>=0 && x < (int) basecpy.width() && y >=0 && y < (int) basecpy.height()) {
				RGBAPixel *pixel = basecpy.getPixel(x,y);
				pixel->r = 255;
				pixel->g = 0;
				pixel->b = 0;

			}
		}
	}
    return basecpy;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

   if(next.first>=this->base.width() || next.first <0) return false;
   if(next.second>=this->base.height() || next.second <0) return false;
   if(v[next.second][next.first]) return false;
   RGBAPixel *pixcurr = this->maze.getPixel(curr.first,curr.second);
   RGBAPixel *nextpix = this->maze.getPixel(next.first,next.second);
   if(!pixcurr->operator==(*nextpix)) return false;
   return true;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {
    // cout << "reached neigh" <<endl;
    vector<pair<int,int>> neighbors_vect;
    neighbors_vect.push_back(make_pair(curr.first-1,curr.second));
    neighbors_vect.push_back(make_pair(curr.first,curr.second-1));
    neighbors_vect.push_back(make_pair(curr.first+1,curr.second));
    neighbors_vect.push_back(make_pair(curr.first,curr.second+1));
    return neighbors_vect;
}