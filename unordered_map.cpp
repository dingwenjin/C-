#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

struct IO_Record {                //value的域
	uint32_t Size;                   //逻辑块大小
	uint16_t hit_count;             //命中率
};

struct Link_Node {                           //key的域
	uint16_t ASU;                        //文件名
	uint32_t LBA;                         //文件的逻辑块地址
};

struct HashFunc {              //hash函数，对自定义的key值进行加密，这里使用或和移位操作可以更加的降低hash冲突
	size_t operator()(const Link_Node &key) const {
		using std::size_t;
		using std::hash;
		return hash<uint16_t>()(key.ASU) ^ hash<uint32_t>()(key.LBA) << 1)) >> 1);
	}
};

struct cmp {                                        //这是一个比较函数，用于比较key是否一样
	bool operator()(const Link_Node &n1, const Link_Node &n2) const {
		return n1.ASU == n2.ASU && n1.LBA == n2.LBA;
	}
};

unordered_map<Link_Node, IO_Record*, HashFunc, cmp> check_request;              //定义一个容器


bool is_exist(Link_Node c) {                                        //判断这个容器中是否存在这个key
	if (check_request.find(c) != check_request.end())
		return true;
	else
		return false;
		
}

void insert_node() {                                //插入节点到容器中，包括key-value
	cout << "start insert node..." << endl;
	cout << "Input request(file_name,lba,size,hit_count): ";

	struct IO_Record *IO_R = new IO_Record;
	Link_Node node;
	cin >> node.ASU >> node.LBA >> IO_R->Size >> IO_R->hit_count;
	check_request.insert(make_pair(node, IO_R));              //将数据插入到容器中

	cout << "finish insert node..." << endl << endl;
}

void check_node() {                           //测试一下容器中是否存在当前输入的key的节点
	cout << "start check node..." << endl;
	cout << "Input request(file_name,lba): ";

	Link_Node node;
	cin >> node.ASU >> node.LBA;
	if (is_exist(node))
		cout << "exist" << endl;
	else
		cout << "not exist" << endl;
	cout << "finish check node..." << endl << endl;
}

void print_node() {                                //打印容器中的节点
	cout << "start print container..." << endl;
	auto it = check_request.begin();
	while (it != check_request.end()) {
		cout << "file name: " << it->first.ASU << "\t" << "lba: " << it->first.LBA << "\t" << "size: " << it->second->Size << "\t" << "hit_count: " << it->second->hit_count << endl;
		it++;
	}
	cout << "finish print container..." << endl << endl;
}

void delete_node() {                                      //删除节点，这里的删除是按照FIFO的方式进行的
	cout << "start delete node..." << endl;
	if (check_request.size() == 0)
		cout << "empty container..." << endl;
	else {
		auto it = check_request.begin();
		IO_Record* IO_R;
		IO_R = it->second;
		delete IO_R;                         //删除完该节点后需要释放该节点的空间
		check_request.erase(it);
	}
	cout << "finish delete node..." << endl << endl;
}

int main() {
	int n;
	cout << "------------------------------------------------------------------" << endl;
	cout << "                                                                  " << endl;
	cout << "                                                                  " << endl;
	cout << "----------------------------1.插入节点----------------------------" << endl;
	cout << "----------------------------2.检查节点----------------------------" << endl;
	cout << "----------------------------3.打印节点----------------------------" << endl;
	cout << "----------------------------4.删除结点----------------------------" << endl;
	cout << "----------------------------5.退出系统----------------------------" << endl;
	cout << "                                                                  " << endl;
	cout << "                                                                  " << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Input your choice: ";
	while (cin >> n) {
		switch (n) {
		case 1:insert_node();
			break;
		case 2:check_node();
			break;
		case 3:print_node();
			break;
		case 4:delete_node();
			break;
		case 5:
			exit(0);
		default:
			cout << "invalid input,please input again!" << endl;
			break;
		}
		cout << "Input your choice: ";
	}

	system("pause");
	return 0;
}