#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

struct IO_Record {                //value����
	uint32_t Size;                   //�߼����С
	uint16_t hit_count;             //������
};

struct Link_Node {                           //key����
	uint16_t ASU;                        //�ļ���
	uint32_t LBA;                         //�ļ����߼����ַ
};

struct HashFunc {              //hash���������Զ����keyֵ���м��ܣ�����ʹ�û����λ�������Ը��ӵĽ���hash��ͻ
	size_t operator()(const Link_Node &key) const {
		using std::size_t;
		using std::hash;
		return hash<uint16_t>()(key.ASU) ^ hash<uint32_t>()(key.LBA) << 1)) >> 1);
	}
};

struct cmp {                                        //����һ���ȽϺ��������ڱȽ�key�Ƿ�һ��
	bool operator()(const Link_Node &n1, const Link_Node &n2) const {
		return n1.ASU == n2.ASU && n1.LBA == n2.LBA;
	}
};

unordered_map<Link_Node, IO_Record*, HashFunc, cmp> check_request;              //����һ������


bool is_exist(Link_Node c) {                                        //�ж�����������Ƿ�������key
	if (check_request.find(c) != check_request.end())
		return true;
	else
		return false;
		
}

void insert_node() {                                //����ڵ㵽�����У�����key-value
	cout << "start insert node..." << endl;
	cout << "Input request(file_name,lba,size,hit_count): ";

	struct IO_Record *IO_R = new IO_Record;
	Link_Node node;
	cin >> node.ASU >> node.LBA >> IO_R->Size >> IO_R->hit_count;
	check_request.insert(make_pair(node, IO_R));              //�����ݲ��뵽������

	cout << "finish insert node..." << endl << endl;
}

void check_node() {                           //����һ���������Ƿ���ڵ�ǰ�����key�Ľڵ�
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

void print_node() {                                //��ӡ�����еĽڵ�
	cout << "start print container..." << endl;
	auto it = check_request.begin();
	while (it != check_request.end()) {
		cout << "file name: " << it->first.ASU << "\t" << "lba: " << it->first.LBA << "\t" << "size: " << it->second->Size << "\t" << "hit_count: " << it->second->hit_count << endl;
		it++;
	}
	cout << "finish print container..." << endl << endl;
}

void delete_node() {                                      //ɾ���ڵ㣬�����ɾ���ǰ���FIFO�ķ�ʽ���е�
	cout << "start delete node..." << endl;
	if (check_request.size() == 0)
		cout << "empty container..." << endl;
	else {
		auto it = check_request.begin();
		IO_Record* IO_R;
		IO_R = it->second;
		delete IO_R;                         //ɾ����ýڵ����Ҫ�ͷŸýڵ�Ŀռ�
		check_request.erase(it);
	}
	cout << "finish delete node..." << endl << endl;
}

int main() {
	int n;
	cout << "------------------------------------------------------------------" << endl;
	cout << "                                                                  " << endl;
	cout << "                                                                  " << endl;
	cout << "----------------------------1.����ڵ�----------------------------" << endl;
	cout << "----------------------------2.���ڵ�----------------------------" << endl;
	cout << "----------------------------3.��ӡ�ڵ�----------------------------" << endl;
	cout << "----------------------------4.ɾ�����----------------------------" << endl;
	cout << "----------------------------5.�˳�ϵͳ----------------------------" << endl;
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