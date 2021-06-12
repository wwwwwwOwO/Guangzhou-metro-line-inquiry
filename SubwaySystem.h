#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <set>
#include <queue>
using namespace std;

class Station{
public:
	string name;//站点名称
	string prev;//从哪个站来
	Station(){	name = "";}
	void set(const string &n) { name = n; }
	void setPrev(const string &p) { prev = p; }
};


class SubwaySystem
{
private:
	map< string, vector<string> > adj_table;	//邻接表记录地铁线路图
	map<string, Station> stations;				//用于记录Station信息：来自哪里；key=站点名称
	map<string, vector<string>> routes;			//用于记录线路信息：线路上的所有站点；key=线路名称
	map< string, set<string> > lines;			//用于记录站点的线路信息：在哪些线路上；key=站点名称
	list<string> theShortestPath;				//用于记录最短线路，包括起始站和终点站

	void print_line(const string &);				//根据线路符合打印线路名称
	void sort_by_lines(vector<string> &);			//根据可换乘的线路数排序，在遍历时先遍历可换乘线路数较少的站点
	string get_line(const string &, const string &);//返回两个站点的相同的线路，用于记录换乘
	
	void Handle_File(const char* name);													 //处理文件信息
	void BFS_Dispose(map<string,bool> &vis_table, const string& from,const string& dest);//广度优先搜得到以得到最短路径
	void Print_ShortestPath();															 //打印最短路径
	void Find_Route(string& start,string& dest);										 //查询最短路径
public:
	SubwaySystem(string filename);	//从文件读入地铁信息
	void Line_Inquiry();			//查询线路信息 
	void Site_Inquiry();			//查询站点信息
	void Route_Inquiry();			//查询线路
};