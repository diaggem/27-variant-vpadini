#include <iostream>
#include <cstring>
using namespace std;

const int N = 20;

enum type { razlomnaya, hrebet, zhelob };

struct ocean {
	char name[25];
};

struct vpad {
	char name[25];
	int depth;
	ocean o;
	type t;
};

const char* t2str(type t) {
	if (t == razlomnaya) return "разломная";
	if (t == hrebet) return "хребет";
	return "желоб";
}

void init(vpad a[], int n) {
	a[0] = { "Марианская", 11034, { "Тихий" }, zhelob };
	a[1] = { "Тонга", 10882, { "Тихий" }, zhelob };
	a[2] = { "Филиппинская", 10540, { "Тихий" }, zhelob };
	a[3] = { "Кермадек", 10047, { "Тихий" }, zhelob };
	a[4] = { "Идзу-Бонин", 9810, { "Тихий" }, zhelob };
	a[5] = { "Курило-Камчатская", 9604, { "Тихий" }, zhelob };
	a[6] = { "Пуэрто-Рико", 8648, { "Атлантический" }, zhelob };
	a[7] = { "Южно-Сандвичева", 8428, { "Атлантический" }, zhelob };
	a[8] = { "Перуанско-Чилийская", 8065, { "Тихий" }, zhelob };
	a[9] = { "Алеутская", 7679, { "Тихий" }, zhelob };
	a[10] = { "Яванская", 7729, { "Индийский" }, zhelob };
	a[11] = { "Романш", 7760, { "Атлантический" }, razlomnaya };
	a[12] = { "Среднеокеанский хребет", 4500, { "Атлантический" }, hrebet };
	a[13] = { "Челенджер", 10920, { "Тихий" }, zhelob };
	a[14] { "Гавайский хребет", 5200, { "Тихий" }, hrebet };
	a[15] = { "Красное море разлом", 3040, { "Индийский" }, razlomnaya };
	a[16] = { "Лорд-Хау", 9500, { "Тихий" }, zhelob };
	a[17] = { "Балтимор", 4400, { "Атлантический" }, hrebet };
	a[18] = { "Африканский разлом", 3800, { "Индийский" }, razlomnaya };
	a[19] = { "Зондский желоб", 7729, { "Индийский" }, zhelob };
}

int deep(vpad a[], int n) {
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (a[i].depth > 6000) cnt++;
	return cnt;
}

int filt(vpad src[], int n, vpad dst[]) {
	int j = 0;
	for (int i = 0; i < n; i++)
		if (src[i].t == zhelob) dst[j++] = src[i];
	return j;
}

void sort(vpad a[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (a[j].depth < a[j + 1].depth)
				swap(a[j], a[j + 1]);
}

void top3(vpad a[], int n) {
	cout << "\nОкеаны 3 глубочайших:\n";
	for (int i = 0; i < 3 && i < n; i++)
		cout << i + 1 << ". " << a[i].name << " - " << a[i].o.name << endl;
}

bool change(vpad a[], int n, int d, const char* nm, const char* oc, type tp) {
	for (int i = 0; i < n; i++) {
		if (a[i].depth == d) {
			strcpy_s(a[i].name, nm);
			strcpy_s(a[i].o.name, oc);
			a[i].t = tp;
			return true;
		}
	}
	return false;
}

int filter(vpad src[], int n, vpad dst[], const char* oc) {
	int j = 0;
	for (int i = 0; i < n; i++)
		if (strcmp(src[i].o.name, oc) == 0)
			dst[j++] = src[i];
	return j;
}

void print(vpad a[], int n, const char* msg) {
	cout << "\n" << msg << ":\n";
	if (!n) { cout << "Нет\n"; return; }
	for (int i = 0; i < n; i++)
		cout << a[i].name << ", " << a[i].depth << " м, "
		<< a[i].o.name << ", " << t2str(a[i].t) << endl;
}

int main() {
	setlocale(LC_ALL, "ru");

	vpad all[N];
	init(all, N);

	cout << ">6000м: " << deep(all, N) << endl;

	vpad tmp[N];
	int cnt = filt(all, N, tmp);
	sort(tmp, cnt);
	print(tmp, cnt, "Желоба");
	top3(tmp, cnt);

	change(all, N, 7729, "НОВАЯ", "Северный Ледовитый", zhelob);

	char oc[25];
	cout << "\nОкеан: ";
	cin.getline(oc, 25);

	vpad res[N];
	int rc = filter(all, N, res, oc);
	print(res, rc, "Результат");

	system("pause");
	return 0;
}
