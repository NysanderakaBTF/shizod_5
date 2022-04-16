#include <iostream>
using namespace std;

class list {
private:
	class node {
	public:
		char data;
		node* next;
		node(char, node* = nullptr);
	};
	node* first;
	node* last;
public:
	list();// конструктор
	bool is_empty();// проверка на пустоту списка
	void push_back(char);// добавление элемента в конец
	void print();// вывод списка на экран
	node* find(char);// посик элемента списка по ключевому полю
	void erase(char);//удаление элемента списка по ключевому полю
	void push_front(char);//втсавка элемента перед первым
	void instert_list(list*, char);//выставка одного списка перед выбранным элементом другого
	void delete_non_digits();//удаление узлов - не цифр из списка
	long long int make_number();//создание числа из цифр списка
	~list();//деструктор
};

list::node::node(char data, node* next)
{
	this->data = data;
	this->next = next;
}

list::list()//инициализания пустого списка
{
	first = nullptr;
	last = nullptr;
}

bool list::is_empty()//проверка на пустоту списка
{
	return first ==nullptr; // если истиина, то значит не существует даже первгого 
														// элемента
}

void list::push_back(char c)//доабавление элемента в конец
{
	node* tmp = new node(c);//создание нового элемента
	if (is_empty()) { //если список пустой, то созданный элемент первый и последний
		first = tmp;
		last = tmp;
	}
	else {
		last->next = tmp;// изменяем указатель бывшего последнего на созданный
		last = tmp;// созданный теперь последний
	}
}

void list::print()// вывод на экран
{
	if (is_empty()) {//если пустой, то нечего печатать
		return;
	}
	else {
		node* t = first;
		while (t!= nullptr) {//идем по списку перемещаясь по указателям до последнего
 			cout << t->data << " ";// и выводим имя каждого элемента
			t = t->next;
		}
	}
	cout << endl;
}

list::node* list::find(char val) // посик элемента по ключу
{
	node* t = first;
	while (t->next != nullptr && t->data != val) t = t->next; //пока это не наш элемент или не конец, идем вперед
	if (t->data == val) return t;//если нашелся, то возвращаем его
	else return nullptr; // не нашелся - возвращаем nullptr
}

void list::erase(char val)//удаление элемента по ключу
{
	if (is_empty()) {// у пустого нечего удалять
		return;
	}
	else if (val == first->data) { // удаление первого элемента
		node* t = first; // переопределяем первый элемент
		first = first->next;
		delete t;
	}
	else if (val == last->data) { // удаление последнего
		node* t = first;
		while (t->next != last)
			t = t->next;
		delete last;//удаялем последний
		t->next = nullptr; // переопределеяем указатель у предпоследнего
		last = t;// переопределяем последний
	}
	else {//удаление в середине
		node* now = first; // перед удаляемым
		node* p_now = first->next; // удаляемый
		while (p_now != nullptr && p_now->data != val) { // ищем удаляемый
			now = now->next;
			p_now = p_now->next;
		}
		if (p_now == nullptr) { // если нет такого ничео не делаем
			cout << val<<" doesnt exist" << endl;
			return;
		}
		now->next = p_now->next; //привязываем элемент после удаляемого к 
		delete p_now;				// элементу перед удаляемым
	}
}

void list::push_front(char ch)//вставка перд первым
{
	node* t = new node(ch, first); // создание нового элемента
	if (is_empty()) { // если пустой список, то t начало и конец
		first = t;
		last = t;
	}
	first = t;// переопределение первого элемента

}

//void list::instert_list(list* li, char af)
//{
//    node* now = find(af);
//    node* li_n = li->first;
//    node* after_li_n = li_n->next;
//    if (now != nullptr) {
//        if (now == first) {
//            while (li_n != nullptr) {
//
//            }
//        }
//        else {
//            while (li_n != nullptr) {
//                li_n->next = now->next;
//                now->next = li_n;
//                li_n = after_li_n;
//                if (li_n != nullptr)
//                    after_li_n = li_n->next;
//                now = now->next;
//            }
//        }
//    }
//    else {
//        cout << af << " doesnt exist" << endl;
//    }
//}
void list::instert_list(list* li, char af)// вставка списка после ключа
{
	node* now = find(af);//поиск ключа
	node* li_n = li->first; //вставляемый элемент
	node* after_li_n = li_n->next; // после вставляемого
	if (now != nullptr) {// если есть ключевой
		if (now == last) {//вставка в конец 
			while (li_n != nullptr) {// каждый элемент списка копируем в конец 
				this->push_back(li_n->data);// с помощью push_back
				li_n = after_li_n;
				if (li_n != nullptr)
					after_li_n = li_n->next;
			}
		}
		else {
			while (li_n != nullptr) {
				node* temp = new node(li_n->data, now->next);//привязываем новый 
									//элемент к следующему за ключевым
				now->next = temp;// ключ привязываем к вставленному
				li_n = after_li_n;
				if (li_n != nullptr)
					after_li_n = li_n->next;
				now = now->next;//переопределение ключа ( чтобы порядок сохранился)
			}
		}
	}
	else {
		cout << af << " doesnt exist" << endl;
	}
}

void list::delete_non_digits()//удаление не цифр
{
	node* now = first;
	node* pos_n = first->next;
	while (now != nullptr) {//проверяем каждый элемент
		if (!isdigit(now->data)) {// не цифра - удаляем
			erase(now->data);
			now = pos_n; // идем дальше по списку
			if(now!=nullptr)
				pos_n = now->next;
		}
		else {
			now = pos_n;// идем дальше по списку
			if (now != nullptr)
				pos_n = now->next;
		}
	}
}

long long int list::make_number()//создание числа из цифр списка
{
	long long int num = 0; 
	node* now = first;
	while (now != nullptr) {
		if (isdigit(now->data)) // если элемент - цифра
			num = num * 10 + (int(now->data) - 48); // приписываем к числу справа
		now = now->next;
	}
	return num;
}

list::~list()//деструктор
{
	if (!is_empty()) {
		node* t = first;
		node* now = first->next;
		while (now != nullptr) {// удаляем элементы с переди, пока не закончатся
			first = now;
			delete t;
			now = first->next;
			t = first;
		}  
		delete t;
	}
}

int main()
{
	list l1, l2;
	int num=0;
	char ch=0,cc;
	bool fill = 1;
	while (true)
	{
		
		if (num == 0) {//ввод списка первый раз 
			cout << "Enter lists manually (1) or load presets (2) ?\nCommand: ";
			cin >> ch;
			if (ch == '1') {//ручной ввод
				cout << "Enter num of elements in list 1" << endl;
				cin >> num;
				cout << "Pushing back(1) or front (2)? " << endl;
				cin >> ch;
				if (ch == '1') {
					cout << "Enter values (chars)" << endl;
					for (int i = 0; i < num; i++) {
						cin >> ch;
						l1.push_back(ch);
					}
				}
				else {
					cout << "Enter values (chars)" << endl;
					for (int i = 0; i < num; i++) {
						cin >> ch;
						l1.push_front(ch);
					}
				}

				cout << "Enter num of elements in list 2" << endl;
				cin >> num;
				cout << "Pushing back(1) or front (2)? " << endl;
				cin >> ch;
				if (ch == '1') {
					cout << "Enter values (chars)" << endl;
					for (int i = 0; i < num; i++) {
						cin >> ch;
						l2.push_back(ch);
					}
				}
				else {
					cout << "Enter values (chars)" << endl;
					for (int i = 0; i < num; i++) {
						cin >> ch;
						l2.push_front(ch);
					}
				}
			}
			else {// пресеты
				cout << "Presets: l1 = q w 2 e 4 r |||  l2 = 7 3 g j" << endl;
				l1.push_back('q'); l2.push_back('7');
				l1.push_back('w'); l2.push_back('3');
				l1.push_back('2'); l2.push_back('g');
				l1.push_back('e'); l2.push_back('j');
				l1.push_back('4');
				l1.push_back('r');
			}
			num = 1;
			cout << "List of commands:\nPrint list (1) \n Erase value by key (2)\nDelete non-digits from list (3)\nMake number from list (4)\nInsert list 2 into list 1 after key (char) (5)\nPush smth back(6)\nPush smth front(7)\n Exit (0)\n";
		}
		else {
			cout << "Command: "; cin >> ch;
			switch (ch)
			{
			case '1'://вывод списков
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				if (ch == '1') l1.print();
				if (ch == '2') l2.print();
				break;
			case '2'://удаление элемента по ключу
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				cout << "Enter key" << endl;
				cin >> cc;
				if (ch == '1') { l1.erase(cc); cout << "list 1: "; l1.print(); }
				if (ch == '2') { l2.erase(cc); cout << "list 2: "; l2.print(); }
				break;
			case '3'://удаление не цифр
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				if (ch == '1') { l1.delete_non_digits(); cout << "list 1: "; l1.print(); }
				if (ch == '2') { l2.delete_non_digits(); cout << "list 2: "; l2.print(); }
				break;
			case '4'://создание числа из списка
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				if (ch == '1') { cout << "Num from list 1: "; cout << l1.make_number() << endl; }
				if (ch == '2') { cout << "Num from list 2: "; cout << l2.make_number() << endl; }
				break;
			case '5'://вставка второго списка в первый
				cout << "Enter key " << endl;
				cin >> ch;
				l1.instert_list(&l2, ch);
				l1.print();
				break;//добавление элемента назад
			case '6':
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				cout << "Value: ";
				cin >> cc;
				if (ch == '1') { l1.push_back(cc); cout << "list 1: "; l1.print(); }
				if (ch == '2') { l2.push_back(cc); cout << "list 2: "; l2.print(); }
				break;
			case '7'://добавление элемента вперед
				cout << "List 1 (1) \\ list 2 (2)?" << endl;
				cin >> ch;
				cout << "Value: ";
				cin >> cc;
				if (ch == '1') { l1.push_front(cc); cout << "list 1: "; l1.print(); }
				if (ch == '2') { l2.push_front(cc); cout << "list 2: "; l2.print(); }
				break;
			case '0':
				return 0;
				break;
			default:
				cout << "Incorrect value" << endl;
				break;
			}
		}
	}
}