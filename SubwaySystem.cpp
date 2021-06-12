#include "SubwaySystem.h"
int SHORT=66666;
bool flag=false;


SubwaySystem::SubwaySystem(string filename){//从文件读入地铁信息
	Handle_File(filename.c_str());
};
void SubwaySystem::Line_Inquiry(){
	cout << endl;
	string line;
	cout << "Line:" << endl;
	cin >> line;
	if (routes.find(line) != routes.end())
	{
		cout << "Stations of ";
		print_line(line);
		cout << " :" << endl;
		for (int i = 0; i < routes[line].size(); ++i){
			cout << routes[line][i];
			if(i!=routes[line].size()-1)
				cout << " - ";
		}
		cout << endl;
	}
}
void SubwaySystem::Site_Inquiry(){
	cout << endl;
	string site;
	getline(cin, site);

	cout << "Site:" << endl;
	getline(cin, site);

	if (lines.find(site) != lines.end()){
		cout << "Line Information:" << endl;//打印所属线路
		for(const auto&a:lines[site]){
			print_line(a);
			cout << endl;
		}
			
		cout << "Adjacent station(s):" << endl;//打印相邻站点名称
		for(const auto&a:adj_table[site])
			cout << a << endl;
	}
}
void SubwaySystem::Route_Inquiry(){
	string start, destination;
	getline(cin, start);

	cout<<"Departure Station:"<<endl;
	getline(cin, start);

	cout<<"Destination:"<<endl;
	getline(cin, destination);

	Find_Route(start, destination);
}


void SubwaySystem::Handle_File(const char* filename)
{
	//从文件读入地铁信息
	ifstream infi(filename, ios::in);
	string line;
	//读入线路名 
	while(getline(infi,line)){
		string temp;
		if ((line.size() <= 2 && isdigit(line[0])) || line == "3_1" || line == "APM" || line == "GF"|| line == "14_1")
		{
			//先输入和处理线路
			Station prev,curr;
			vector<string> route;
			while(getline(infi,temp)){//输入和处理站点
				if(temp.size()==0)
					break;
				curr.set(temp);
				stations[temp]=curr;
				lines[temp].insert(line);
				route.push_back(temp);
				if(prev.name!=""){
					adj_table[temp].push_back(prev.name);//图记录：上一站的站点名称、线路名称
					adj_table[prev.name].push_back(temp);
				}
				prev = curr;
			}
			if(!route.empty())
				routes[line] = route;
		}
	}
}

void SubwaySystem::BFS_Dispose(map<string,bool> &vis_table,const string& start,const string& destination)
{
	queue<string> wait;

	wait.push(start);//将起始站推入队列
	vis_table[start]=true;

	string curr;
	//广搜
	while(!wait.empty())
	{
		curr = wait.front();
		if (curr == destination)//若搜到目标站点
		{
			//将经过的站点存储到最短路径的容器中
			string mark = curr;
			while(mark!=start){
				theShortestPath.push_front(mark);
				mark = stations[mark].prev;
			}
			theShortestPath.push_front(start);//存入起始站
			return;
		}
		sort_by_lines(adj_table[curr]);//根据可换乘车站的数目进行排序，先访问可换乘车站的数目少的站点，从而使最短路径的是所有等长路径中换乘次数最少的

		for (auto a:adj_table[curr])
		{
			if(!vis_table[a]){
				stations[a].setPrev(curr);
				wait.push(a);
				vis_table[a] = true;
			}
		}
		wait.pop();	
	}
}
string SubwaySystem::get_line(const string &a, const string &b){
	//找到并返回两个车站都属于的线路
	for(const auto &e:lines[a]){
		if(lines[b].count(e))
			return e;
	}
	return "";
}
void SubwaySystem::print_line(const string &line){
	if(line=="3_1")//3号线北延段
		cout << "North extension of Line 3";
	else if(line=="14_1")//14号线支线
		cout << "Extension of Line 14";
	else
		cout << "Line " << line;
}
void SubwaySystem::sort_by_lines(vector<string> &v){
	for (int i = v.size() - 1; i > 0; i--)
	{
		for (int j = 1; j <= i;j++){
			if(lines[v[j]].size()<lines[v[j-1]].size()){
				string temp = v[j - 1];
				v[j - 1] = v[j];
				v[j] = temp;
			}
		}
	}
}
void SubwaySystem::Print_ShortestPath(){
	if(theShortestPath.size()<2)
		return;
		
	auto curr = theShortestPath.begin(), next = curr;
	++next;//记录下一个车站
	string line = get_line(*curr, *next);
	print_line(line);
	cout << ": ";
	while(next!=theShortestPath.end()){
		if(get_line(*curr,*next)!=line){//该站和下一个站都属于的线路和当前线路不同说明需要换乘
			line = get_line(*curr, *next);
			cout << *curr;
			cout << "(Tranfer to ";
			print_line(line);
			cout << ")" << endl;
			print_line(line);
			cout << ": ";
		}
		else
			cout << *curr << " ---> ";
		curr = next;
		next++;
	}
	//打印终点站
	cout << *curr << endl;
	cout << "A total of " << theShortestPath.size() - 1 << " stations." << endl;
}


void SubwaySystem::Find_Route(string& start,string& destination)
{
	if(stations.find(start)!=stations.end()&&stations.find(destination)!=stations.end()&&start!=destination){
		map<string, bool> vis_table;
		for(auto a:stations)
			vis_table[a.first] = false;

		BFS_Dispose(vis_table,start,destination);
		cout << endl;
		cout << "The shortest path:" << endl;
		Print_ShortestPath();
	}
	else if(stations.find(start)==stations.end())
		cout << "Missing departure station." << endl;
	else if(stations.find(destination)==stations.end())
		cout << "Missing destination." << endl;
	else
		cout << "The departure station is the same as the destination."<<endl;	
}
