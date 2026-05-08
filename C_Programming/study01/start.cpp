#include <iostream> //표준 입출력 헤더파일

#if 0
int main(void) {
	//std == C++ 표준 라이브러리의 모든 함수, 객체 등이 정의된 이름 공간(namespace)
	//같은 이름이라도,소속된 이름 공간 이 다르면 다른 것으로 취급
	std::cout << "Hello, world!!!" << std::endl;
	
	return 0;
}
#endif //first

#if 0
int main(void) {
	
	std::cout << "Hello" << std::endl
		<< "my name is "
		<< "psi" << std::endl;

	return 0;
}
#endif // ex1

#if 0
int main(void) {
	int sum = 0;
	for (int i = 0; i <= 10; ++i) {
		sum += i;
	}

	std::cout << "sum : " << sum << std::endl;

	return 0;
}
#endif // for

#if 0
int main(void) {
	int sum = 0;
	int i = 0;
	while (i <= 10) {
		sum += i;
		i++;
	}

	std::cout << "sum : " << sum << std::endl;

	return 0;
}
#endif // while

#if 0
int main() {
	int lucky_number = 3;
	std::cout << "내 비밀 수를 맞추어 보세요~" << std::endl;
	int user_input; // 사용자 입력
	while (1) {
		std::cout << "입력 : ";
		std::cin >> user_input;
		if (lucky_number == user_input) {
			std::cout << "맞추셨습니다~~" << std::endl;
			break;
		}
		else {
			std::cout << "다시 생각해보세요~" << std::endl;
		}
	}
	return 0;
}
#endif // if else

#if 0
using std::cout;
using std::endl;
using std::cin;
int main() {
	int user_input;
	cout << "저의 정보를 표시해줍니다" << endl;
	cout << "1. 이름 " << endl;
	cout << "2. 나이 " << endl;
	cout << "3. 성별 " << endl;
	cin >> user_input;
	switch (user_input) {
	case 1:
		cout << "Psi ! " << endl;
		break;
	case 2:
		cout << "99 살" << endl;
		break;
	case 3:
		cout << "남자" << endl;
		break;
	default:
		cout << "궁금한게 없군요~" << endl;
		break;
	}
	return 0;
}
#endif //switch case

/*-----------------------------------*/

#if 0
int main() {
	int a = 3;
	int& another_a = a;
	another_a = 5;
	std::cout << "a : " << a << std::endl;
	std::cout << "another_a : " << another_a << std::endl;
	return 0;
}

#endif //reference intro

#if 0
int change_val(int& p) {
	p = 3;
	return 0;
}
int main() {
	int number = 5;
	std::cout << number << std::endl;
	change_val(number);
	std::cout << number << std::endl;
}

#endif //reference in func

#if 0
int main() {
	int x;
	int& y = x;
	int& z = y;
	x = 1;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
	y = 2;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
	z = 3;
	std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
}

#endif //reference ex

#if 0
int main() {
	int arr[3] = { 1, 2, 3 };
	int(&ref)[3] = arr;
	ref[0] = 2;
	ref[1] = 3;
	ref[2] = 1;
	std::cout << arr[0] << arr[1] << arr[2] << std::endl;
	return 0;
}
#endif //reference of array

#if 0
int& function(int& a) {
	a = 5;
	return a;
}
int main() {
	int b = 2;
	int c = function(b);
	return 0;
}
#endif //reference return (extern value)

#if 0
int function() {
	int a = 5;
	return a;
}
int main() {
	const int& c = function();
	std::cout << "c : " << c << std::endl;
	return 0;
}
#endif //reference return (possible ex)

/*--------------------------------------------*/

#if 0
/* new 와 delete 의 사용 */
int main() {
	int* p = new int;
	*p = 10;
	std::cout << *p << std::endl;
	delete p;
	return 0;
}
#endif //new, delete

#if 0
int main() {
	int arr_size;
	std::cout << "array size : ";
	std::cin >> arr_size;
	int* list = new int[arr_size];
	for (int i = 0; i < arr_size; i++) {
		std::cin >> list[i];
	}
	for (int i = 0; i < arr_size; i++) {
		std::cout << i << "th element of list : " << list[i] << std::endl;
	}
	delete[] list;
	return 0;
}
#endif // new, delete of array


/*----------------------------*/

#if 0
class Animal {
private:
	int food;
	int weight;
public:
	void set_animal(int _food, int _weight) {
		food = _food;
		weight = _weight;
	}
	void increase_food(int inc) {
		food += inc;
		weight += (inc / 3);
	}
	void view_stat() {
		std::cout << "이 동물의 food : " << food << std::endl;
		std::cout << "이 동물의 weight : " << weight << std::endl;
	}
}; // 세미콜론 잊지 말자!
int main() {
	Animal animal;
	animal.set_animal(100, 50);
	animal.increase_food(30);
	animal.view_stat();
	return 0;
}
#endif //class, instance

#if 0
void print(int x) { std::cout << "int : " << x << std::endl; }
void print(char x) { std::cout << "char : " << x << std::endl; }
void print(double x) { std::cout << "double : " << x << std::endl; }
int main() {
	int a = 1;
	char b = 'c';
	double c = 3.2f;
	print(a);
	print(b);
	print(c);
	return 0;
}
#endif  //function overloading

#if 0

class Date {

		int year_;
	int month_; // 1 부터 12 까지.
	int day_; // 1 부터 31 까지.
public:
	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	// 해당 월의 총 일 수를 구한다.
	int GetCurrentMonthTotalDays(int year, int month);
	void ShowDate();
};
void Date::SetDate(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}
int Date::GetCurrentMonthTotalDays(int year, int month) {
	static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month != 2) {
		return month_day[month - 1];
	}
	else if (year % 4 == 0 && year % 100 != 0) {
		return 29; // 윤년
	}
	else {
		return 28;
	}
}
void Date::AddDay(int inc) {
	while (true) {
		// 현재 달의 총 일 수
		int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);
		// 같은 달 안에 들어온다면;
		if (day_ + inc <= current_month_total_days) {
			day_ += inc;
			return;
		}
		else {
			// 다음달로 넘어가야 한다.
			inc -= (current_month_total_days - day_ + 1);
			day_ = 1;
			AddMonth(1);
		}
	}
}

void Date::AddMonth(int inc) {
	AddYear((inc + month_ - 1) / 12);
	month_ = month_ + inc % 12;
	month_ = (month_ == 12 ? 12 : month_ % 12);
}
void Date::AddYear(int inc) { year_ += inc; }
void Date::ShowDate() {
	std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
		<< " 일 입니다 " << std::endl;
}
int main() {
	Date day;
	day.SetDate(2011, 3, 1);
	day.ShowDate();
	day.AddDay(30);
	day.ShowDate();
	day.AddDay(2000);
	day.ShowDate();
	day.SetDate(2012, 1, 31); // 윤년
	day.AddDay(29);
	day.ShowDate();
	day.SetDate(2012, 8, 4);
	day.AddDay(2500);
	day.ShowDate();
	return 0;
}

#endif //date

#if 0
class Date {
	int year_;
	int month_; // 1 부터 12 까지.
	int day_; // 1 부터 31 까지.
public:
	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	// 해당 월의 총 일 수를 구한다.
	int GetCurrentMonthTotalDays(int year, int month);
	void ShowDate();
	Date(int year, int month, int day) {
		year_ = year;
		month_ = month;
		day_ = day;
	}
};
// 생략
void Date::AddYear(int inc) { year_ += inc; }
void Date::ShowDate() {
	std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
		<< " 일 입니다 " << std::endl;
}
int main() {
	Date day(2011, 3, 1);
	day.ShowDate();
	day.AddYear(10);
	day.ShowDate();
	return 0;
}

#endif //constructor

#if 0
class Date {
	int year_;
	int month_; // 1 부터 12 까지.
	int day_; // 1 부터 31 까지.
public:
	void ShowDate();
		Date() {
		year_ = 2012;
		month_ = 7;
		day_ = 12;
	}
};
void Date::ShowDate() {
	std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
		<< " 일 입니다 " << std::endl;
}
int main() {
	Date day = Date();
	Date day2;
	day.ShowDate();
	day2.ShowDate();
	return 0;
}
#endif  //default constructor

#if 0
class Date {
	int year_;
	int month_; // 1 부터 12 까지.
	int day_; // 1 부터 31 까지.
public:
	void ShowDate();
		Date() {
		std::cout << "기본 생성자 호출!" << std::endl;
		year_ = 2012;
		month_ = 7;
		day_ = 12;
	}
	Date(int year, int month, int day) {
		std::cout << "인자 3 개인 생성자 호출!" << std::endl;
		year_ = year;
		month_ = month;
		day_ = day;
	}
};
void Date::ShowDate() {
	std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
		<< " 일 입니다 " << std::endl;
}
int main() {
	Date day = Date();
	Date day2 = Date(2012, 10, 31);
	day.ShowDate();
	day2.ShowDate();
	return 0;
}
#endif //constructor overload


#if 0
class Marine {
	int hp; // 마린 체력
	int coord_x, coord_y; // 마린 위치
	int damage; // 공격력
	bool is_dead;
public:
	Marine(); // 기본 생성자
	Marine(int x, int y); // x, y 좌표에 마린 생성
	int attack(); // 데미지를 리턴한다.
	void be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치
	void show_status(); // 상태를 보여준다.
};
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}
int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);
	marine1.show_status();
	marine2.show_status();
}

#endif //init list

#if 0
class Marine {
	int hp; // 마린 체력
	int coord_x, coord_y; // 마린 위치
	bool is_dead;
	const int default_damage; // 기본 공격력
public:
	Marine(); // 기본 생성자
	Marine(int x, int y); // x, y 좌표에 마린 생성
	int attack(); // 데미지를 리턴한다.
	void be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치
	void show_status(); // 상태를 보여준다.
};
Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
}
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
}
int main() {
	Marine marine1(2, 3);
	Marine marine2(3, 5);
	marine1.show_status();
	marine2.show_status();
		std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());
	marine1.show_status();
	marine2.show_status();
}
#endif //init list 2

#if 0
class Marine {
	static int total_marine_num;
	int hp; // 마린 체력
	int coord_x, coord_y; // 마린 위치
	bool is_dead;
	const int default_damage; // 기본 공격력
public:
	Marine(); // 기본 생성자
	Marine(int x, int y); // x, y 좌표에 마린 생성
	Marine(int x, int y, int default_damage);
	int attack(); // 데미지를 리턴한다.
	void be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치
	void show_status(); // 상태를 보여준다.
	~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}

Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {
	total_marine_num++;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}
void create_marine() {
	Marine marine3(10, 10, 4);
	marine3.show_status();
}
int main() {
	Marine marine1(2, 3, 5);
	marine1.show_status();
	Marine marine2(3, 5, 10);
	marine2.show_status();
	create_marine();
	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());
	marine1.show_status();
	marine2.show_status();
}
#endif //static v

#if 0
class Marine {
	static int total_marine_num;
	const static int i = 0;
	int hp; // 마린 체력
	int coord_x, coord_y; // 마린 위치
		bool is_dead;
	const int default_damage; // 기본 공격력
public:
	Marine(); // 기본 생성자
	Marine(int x, int y); // x, y 좌표에 마린 생성
	Marine(int x, int y, int default_damage);
	int attack(); // 데미지를 리턴한다.
	void be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치
	void show_status(); // 상태를 보여준다.
	static void show_total_marine();
	~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}
Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y)
	: coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {
	total_marine_num++;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;

		std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}
void create_marine() {
	Marine marine3(10, 10, 4);
	Marine::show_total_marine();
}
int main() {
	Marine marine1(2, 3, 5);
	Marine::show_total_marine();
	Marine marine2(3, 5, 10);
	Marine::show_total_marine();
	create_marine();
	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
	marine2.be_attacked(marine1.attack());
	marine1.show_status();
	marine2.show_status();
}

#endif //static func

#if 0
class A {
	int x;
public:
	A(int c) : x(c) {}
	int& access_x() { return x; }
	int get_x() { return x; }
	void show_x() { std::cout << x << std::endl; }
};
int main() {
	A a(5);
	a.show_x();
	int& c = a.access_x();
	c = 4;
	a.show_x();
	int d = a.access_x();
	d = 3;
	a.show_x();
	// 아래는 오류
	// int& e = a.get_x();
	// e = 2;
	// a.show_x();
	int f = a.get_x();
	f = 1;
	a.show_x();
}

#endif // reference return func

#if 0
class Marine {
	static int total_marine_num;
	const static int i = 0;
	int hp; // 마린 체력
	int coord_x, coord_y; // 마린 위치
	bool is_dead;
	const int default_damage; // 기본 공격력
public:
	Marine(); // 기본 생성자
	Marine(int x, int y); // x, y 좌표에 마린 생성
	Marine(int x, int y, int default_damage);
	int attack() const; // 데미지를 리턴한다.
	Marine& be_attacked(int damage_earn); // 입는 데미지
	void move(int x, int y); // 새로운 위치
	void show_status(); // 상태를 보여준다.
		static void show_total_marine();
	~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}
Marine::Marine()
	: hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(5),
	is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage)
	: coord_x(x),
	coord_y(y),
	hp(50),
	default_damage(default_damage),
	is_dead(false) {
	total_marine_num++;
}
void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() const { return default_damage; }
Marine& Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
	return *this;
}
void Marine::show_status() {
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
		<< std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}
int main() {
		Marine marine1(2, 3, 5);
	marine1.show_status();
	Marine marine2(3, 5, 10);
	marine2.show_status();
	std::cout << std::endl << "마린 1 이 마린 2 를 두 번 공격! " << std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
	marine1.show_status();
	marine2.show_status();
}

#endif //const func

#if 0
#include <vector>
int main() {
	std::vector<int> vec;
	vec.push_back(10); // 맨 뒤에 10 추가
	vec.push_back(20); // 맨 뒤에 20 추가
	vec.push_back(30); // 맨 뒤에 30 추가
	vec.push_back(40); // 맨 뒤에 40 추가
	//for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
	for (auto i = 0; i < vec.size(); i++) {
		std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
	}
}

#endif  //vector start

#if 0
#include <vector>
int main() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);
	// 전체 벡터를 출력하기
	//for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
	for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
	// int arr[4] = {10, 20, 30, 40}
	// *(arr + 2) == arr[2] == 30;
	// *(itr + 2) == vec[2] == 30;
	std::vector<int>::iterator itr = vec.begin() + 2;
	std::cout << "3 번째 원소 :: " << *itr << std::endl;
}

#endif  //iterator

#if 0
#include <vector>
template <typename T>
void print_vector(std::vector<T>& vec) {
	// 전체 벡터를 출력하기
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
		++itr) {
		std::cout << *itr << std::endl;
	}
}
int main() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);
	std::cout << "처음 벡터 상태" << std::endl;
	print_vector(vec);
	std::cout << "----------------------------" << std::endl;
	// vec[2] 앞에 15 추가
	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);
		std::cout << "----------------------------" << std::endl;
	// vec[3] 제거
	vec.erase(vec.begin() + 3);
	print_vector(vec);
}

#endif //iterator cal

#if 0
#include <vector>
int main() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(2);
	vec.push_back(3);
	// range-based for 문
	for (int elem : vec) {
		std::cout << "원소 : " << elem << std::endl;
	}
	return 0;
}
#endif // ather for

#if 0
#include <list>
int main() {
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);
	//for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
	for (auto itr = lst.begin(); itr != lst.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
}
#endif  //list

#if 0
#include <deque>
#include <iostream>
template <typename T>
void print_deque(std::deque<T>& dq) {
	// 전체 덱을 출력하기
	std::cout << "[ ";
	for (const auto& elem : dq) {
		std::cout << elem << " ";
	}
	std::cout << " ] " << std::endl;
}
int main() {
	std::deque<int> dq;
	dq.push_back(10);
	dq.push_back(20);
	dq.push_front(30);
	dq.push_front(40);
	std::cout << "초기 dq 상태" << std::endl;
	print_deque(dq);
	std::cout << "맨 앞의 원소 제거" << std::endl;
	dq.pop_front();
	print_deque(dq);
}
#endif  //deque

#if 0
#include <iostream>
#include <set>
template <typename T>
void print_set(std::set<T>& s) {
	// 셋의모든원소들을출력하기
	std::cout << "[ ";
	for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
		std::cout << *itr << " ";
	}
	std::cout << " ] " << std::endl;
}
int main() {
	std::set<int> s;
	s.insert(10);
	s.insert(50);
	s.insert(20);
	s.insert(40);
	s.insert(30);
	std::cout << "순서대로정렬되서나온다" << std::endl;
	print_set(s);
	std::cout << "20 이s 의원소인가요? :: ";
	auto itr = s.find(20);
	if (itr != s.end()) {
		std::cout << "Yes" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	std::cout << "25 가s 의원소인가요? :: ";
	itr = s.find(25);
	if (itr != s.end()) {
			std::cout << "Yes" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
}
#endif //set

#if 0
#include <set>
#include <string>

typedef struct Todo {
	int priority;
	std::string job_desc;
	// const 속성을 반드시 붙여야 합니다 (set의 정렬 기준은 변하면 안 되기 때문)
	bool operator<(const Todo& other) const {
		if (priority == other.priority) {
			// 우선순위가 같다면 문자열로 비교하여 중복 방지
			return job_desc < other.job_desc;
		}
		// 우선순위가 높은(값이 큰) 것이 먼저 오게 하려면 'priority > other.priority'
		// 기본적으로 낮은 순서부터 정렬하려면 아래와 같이 작성
		return priority < other.priority;
	}

}Todo;

// 출력 함수에서도 Todo 객체를 다룰 수 있도록 수정이 필요합니다.
void print_set(const std::set<Todo>& s) {
	std::cout << "[ \n";
	for (const auto& elem : s) {
		std::cout << "  Priority: " << elem.priority << " - " << elem.job_desc << "\n";
	}
	std::cout << " ] " << std::endl;
}
int main() {
	std::set<Todo> todos;

	Todo tmp = { 1, "농구 하기" };
	todos.insert(tmp);
	tmp = {2, "수학 숙제하기"};
	todos.insert(tmp);
	tmp = { 3, "탐구 숙제하기" };
	todos.insert(tmp);
	tmp = { 4, "과학 숙제하기" };
	todos.insert(tmp);
	tmp = { 5, "메이플 숙제하기" };
	todos.insert(tmp);
	print_set(todos);
}
#endif //operator 의 선언을 통한 정렬기준 확보

#if 0
#include <map>
#include <string>
template <typename K, typename V>
void print_map(std::map<K, V>& m) {
	// 맵의모든원소들을출력하기
	for (auto itr = m.begin(); itr != m.end(); ++itr) {
		std::cout << itr->first << " " << itr->second << std::endl;
	}
}
int main() {
	std::map<std::string, double> pitcher_list;
	// 참고로2017년7월4일현재투수방어율순위입니다.
	// 맵의insert 함수는pair 객체를인자로받습니다.
	pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
	pitcher_list.insert(std::pair<std::string, double>("해커 ", 2.93));
	pitcher_list.insert(std::pair<std::string, double>("피어밴드 ", 2.95));
	// 타입을지정하지않아도간단히std::make_pair 함수로
	// std::pair 객체를만들수도있습니다.
	pitcher_list.insert(std::make_pair("차우찬", 3.04));
	pitcher_list.insert(std::make_pair("장원준 ", 3.05));
	pitcher_list.insert(std::make_pair("헥터 ", 3.09));
	// 혹은insert 를안쓰더라도[] 로바로
	// 원소를추가할수있습니다.
	pitcher_list["니퍼트"] = 3.56;
	pitcher_list["박종훈"] = 3.76;
	pitcher_list["켈리"] = 3.90;
		print_map(pitcher_list);
	std::cout << "박세웅방어율은? :: " << pitcher_list["박세웅"] << std::endl;
}
#endif //map

#if 0
#include <iostream>
#include <map>
#include <string>
template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
	// kv 에는맵의key 와value 가std::pair 로들어갑니다.
	for (const auto& kv : m) {
		std::cout << kv.first << " " << kv.second << std::endl;
	}
}
template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
	auto itr = m.find(key);
	if (itr != m.end()) {
		std::cout << key << "--> " << itr->second << std::endl;
	}
	else {
		std::cout << key << "은(는) 목록에없습니다" << std::endl;
	}
}
int main() {
	std::map<std::string, double> pitcher_list;
	pitcher_list["오승환"] = 3.58;
	print_map(pitcher_list);
	std::cout << "-----------------" << std::endl;
	search_and_print(pitcher_list, std::string("오승환"));
	search_and_print(pitcher_list, std::string("류현진"));
}

#endif //map + find

#if 0
#include <iostream>
#include <string>
#include <unordered_set>
template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
	// 셋의모든원소들을출력하기
	for (const auto& elem : m) {
		std::cout << elem << std::endl;
	}
}
int main() {
	std::unordered_set<std::string> s;
	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("hi");
	s.insert("is");
	s.insert("psi");
	s.insert("welcome");
		s.insert("to");
	s.insert("c++");
	print_unordered_set(s);
}
#endif  //unordered set

#if 0
#include <iostream>
#include <string>
#include <unordered_set>
template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
	// 셋의모든원소들을출력하기
	for (const auto& elem : m) {
		std::cout << elem << std::endl;
	}
}
template <typename K>
void is_exist(std::unordered_set<K>& s, K key) {
	auto itr = s.find(key);
	if (itr != s.end()) {
		std::cout << key << " 가존재!" << std::endl;
	}
	else {
		std::cout << key << " 가없다" << std::endl;
	}
}
int main() {
	std::unordered_set<std::string> s;
	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("psi");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	print_unordered_set(s);
	std::cout << "----------------" << std::endl;
	is_exist(s, std::string("c++"));
	is_exist(s, std::string("c"));
	std::cout << "----------------" << std::endl;
	std::cout << "'hi' 를삭제" << std::endl;
	s.erase(s.find("hi"));
	is_exist(s, std::string("hi"));
}
#endif //unordered set 2

/*  ---------------------------------------------------  */
#if 0
#include <algorithm>
#include <iostream>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);
	std::cout << "정렬 전 ----" << std::endl;
	print(vec.begin(), vec.end());

	std::sort(vec.begin(), vec.end());

	std::cout << "정렬 후 ----" << std::endl;
	print(vec.begin(), vec.end());
}

#endif //sort 1

#if 0
#include <algorithm>
#include <iostream>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}
template <typename T>
struct greater_comp {
		bool operator()(const T & a, const T & b) const { return a > b; }
};

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);
	std::cout << "정렬 전 ----" << std::endl;
	print(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end(), greater_comp<int>());
	std::cout << "정렬 후 ----" << std::endl;
	print(vec.begin(), vec.end());
}

#endif //sort 2

#if 0
#include <algorithm>
#include <iostream>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);
	std::cout << "정렬 전 ----" << std::endl;
	print(vec.begin(), vec.end());
	std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
	std::cout << "정렬 후 ----" << std::endl;
	print(vec.begin(), vec.end());
}
#endif //partial_sort

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
struct User {
	std::string name;
	int age;
	User(std::string name, int age) : name(name), age(age) {}
	bool operator<(const User& u) const { return age < u.age; }
};
std::ostream& operator<<(std::ostream& o, const User& u) {
	o << u.name << " , " << u.age;
	return o;
}
int main() {
	std::vector<User> vec;
	for (int i = 0; i < 100; i++) {
		std::string name = "";
		name.push_back('a' + i / 26);
		name.push_back('a' + i % 26);
		vec.push_back(User(name, static_cast<int>(rand() % 10)));
	}
	std::vector<User> vec2 = vec;
	std::cout << "정렬 전 ----" << std::endl;
	print(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end());
	std::cout << "정렬 후 ----" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "stable_sort 의 경우 ---" << std::endl;
	std::stable_sort(vec2.begin(), vec2.end());
	print(vec2.begin(), vec2.end());
}

#endif  //stable sort


/*----------------------------*/

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "벡터에서 값이 3 인 원소 제거 ---" << std::endl;
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
	print(vec.begin(), vec.end());
}
#endif //remove

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
struct is_odd {
	bool operator()(const int& i) { return i % 2 == 1; }
};
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "벡터에서 홀수 인 원소 제거 ---" << std::endl;
	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
	print(vec.begin(), vec.end());
}

#endif //remove_if


#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[](int i) -> bool { return i % 2 == 1; }),
		vec.end());
	print(vec.begin(), vec.end());
}
#endif  //lambda

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "벡터에서 홀수인 원소 ---" << std::endl;
	int num_erased = 0;
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[&num_erased](int i) {
			if (num_erased >= 2)
				return false;
			else if (i % 2 == 1) {
				num_erased++;
				return true;
			}
			return false;
		}),
		vec.end());
	print(vec.begin(), vec.end());
}
#endif //lambda capture list

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());
	std::cout << "벡터 전체에 1 을 더한다" << std::endl;
	std::transform(vec.begin(), vec.end(), vec.begin(),
		[](int i) { return i + 1; });
	print(vec.begin(), vec.end());
}

#endif  //transform

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	auto result = std::find(vec.begin(), vec.end(), 3);
	std::cout << "3 은 " << std::distance(vec.begin(), result) + 1 << " 번째 원소"
		<< std::endl;
}
#endif //find 1

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	auto current = vec.begin();
	while (true) {
		current = std::find(current, vec.end(), 3);
		if (current == vec.end()) break;
		std::cout << "3 은 " << std::distance(vec.begin(), current) + 1
			<< " 번째 원소" << std::endl;
		current++;
	}
}
#endif //find 2

#if 0
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}
int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	auto current = vec.begin();
	while (true) {
		current =
			std::find_if(current, vec.end(), [](int i) { return i % 3 == 2; });
		if (current == vec.end()) break;
		std::cout << "3 으로 나눈 나머지가 2 인 원소는 : " << *current << " 이다 "
			<< std::endl;
		current++;
	}
}

#endif  //find_if


/*---------------------------------------*/
#if 0
#include <iostream>
#include <string>
int main() {
	std::string s = "abc";
	std::string t = "def";
	std::string s2 = s;
	std::cout << s << " 의 길이 : " << s.length() << std::endl;
	std::cout << s << " 뒤에 " << t << " 를 붙이면 : " << s + t << std::endl;
	if (s == s2) {
		std::cout << s << " 와 " << s2 << " 는 같다 " << std::endl;
	}
	if (s != t) {
		std::cout << s << " 와 " << t << " 는 다르다 " << std::endl;
	}
	return 0;
}

#endif //string

#if 0
#include <iostream>
#include <string>
using namespace std::literals;
int main() {
	auto s1 = "hello"s;
	std::cout << "s1 길이 : " << s1.size() << std::endl;
}

#endif //literal

#if 0
#include <iostream>
#include <string>
int main() {
	std::string str = R"(asdfasdf
이 안에는
어떤 것들이 와도ok
// 이런것도 되고
#define hasldfjalskdfj
\n\n <--- Escape 안해도 됨
)";
	std::cout << str;
}

#endif //literal 2

#if 0
#include <iostream>
#include <string>
int main() {
	std::string str = R"fooo(
)"; <-- 무시됨
)fooo";
	std::cout << str;
}

#endif //literal 3

#if 0
void* operator new(std::size_t count) {
	std::cout << count << " bytes 할당 " << std::endl;
	return malloc(count);
}
// 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
bool contains_very(const std::string & str) {
	return str.find("very") != std::string::npos;
}
int main() {
	// 암묵적으로 std::string 객체가 불필요하게 생성된다.
	std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
		<< std::endl;
	std::cout << contains_very("c++ string is not easy to use") << std::endl;
}

#endif //why string view need?

#if 01
#include <iostream>
#include <string>
void* operator new(std::size_t count) {
	std::cout << count << " bytes 할당 " << std::endl;
	return malloc(count);
}
// 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
bool contains_very(std::string_view str) {
	return str.find("very") != std::string_view::npos;
}
int main() {
	// string_view 생성 시에는 메모리 할당이 필요 없다.
	std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
		<< std::endl;
		std::cout << contains_very("c++ string is not easy to use") << std::endl;
	std::string str = "some long string";
	std::cout << "--------------------" << std::endl;
	std::cout << contains_very(str) << std::endl;
}

#endif  //string_view