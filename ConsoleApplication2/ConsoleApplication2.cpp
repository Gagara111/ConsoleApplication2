/**
 * Сохранение баз данных финансового рынка за прошлый месяц:
 * Срочный рынок (на нефть и золото) - Акции (Сбербанк) - Индексы (РТС)
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Trade {
    string instrument; // название инструмента
    string time; // время сделки
    double price; // цена
    int volume; // объем
    bool marketOrder; // покупка на рынке или по лимитному ордеру
};

struct Market {
    string name; // название рынка
    vector<Trade> trades; // список сделок на рынке
};

vector<Market> markets{
    {"Oil Futures", {}},
    {"Gold Futures", {}},
    {"Sberbank Stocks", {}},
    {"RTS Index", {}}
};

/**
 * Чтение базы данных сделок из файлов
 */
void readTradesFromFile(const string& filename, vector<Trade>& trades) {
    ifstream file;
    file.open(filename);
    if (!file) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }
    Trade trade;
    while (file >> trade.instrument >> trade.time >> trade.price >> trade.volume >> trade.marketOrder) {
        trades.push_back(trade);
    }
    file.close();
}

/**
 * Запись базы данных сделок в файл
 */
void writeTradesToFile(const string& filename, const vector<Trade>& trades) {
    ofstream file;
    file.open(filename);
    if (!file) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }
    for (const auto& trade : trades) {
        file << trade.instrument << " " << trade.time << " " << trade.price
            << " " << trade.volume << " " << trade.marketOrder << endl;
    }
    file.close();
}

/**
 * Вывод параметров инструмента по выбранной сделке
 */
void printInstrumentParams(const Trade& trade) {
    cout << "Instrument Name: " << trade.instrument << endl;
    cout << "Time: " << trade.time << endl;
    cout << "Price: " << trade.price << endl;
    cout << "Volume: " << trade.volume << endl;
    if (trade.marketOrder) {
        cout << "Order Type: Market Order" << endl;
    }
    else {
        cout << "Order Type: Limit Order" << endl;
    }
}

/**
 * Вывод меню выбора инструмента
 */
void printInstrumentMenu(const vector<Trade>& trades) {
    int choice = -1;
    while (choice < 0 || choice >= trades.size()) {
        cout << "Choose an instrument: " << endl;
        for (int i = 0; i < trades.size(); ++i) {
            cout << i << ". " << trades[i].instrument << endl;
        }
        cin >> choice;
    }
    printInstrumentParams(trades[choice]);
}

/**
 * Вывод меню выбора рынка
 */
void printMarketMenu(const vector<Market>& markets) {
    int choice = -1;
    while (choice < 0 || choice >= markets.size()) {
        cout << "Choose a market: " << endl;
        for (int i = 0; i < markets.size(); ++i) {
            cout << i << ". " << markets[i].name << endl;
        }
        cin >> choice;
    }
    printInstrumentMenu(markets[choice].trades);
}

/**
 * Точка входа в программу
 */
int main() {
    // Чтение базы данных сделок из файлов
    readTradesFromFile("oil_futures.txt", markets[0].trades);
    readTradesFromFile("gold_futures.txt", markets[1].trades);
    readTradesFromFile("sberbank_stocks.txt", markets[2].trades);
    readTradesFromFile("rts_index.txt", markets[3].trades);

    // Запись базы данных сделок в файлы
    writeTradesToFile("oil_futures.txt", markets[0].trades);
    writeTradesToFile("gold_futures.txt", markets[1].trades);
    writeTradesToFile("sberbank_stocks.txt", markets[2].trades);
    writeTradesToFile("rts_index.txt", markets[3].trades);

    // Вывод меню и отображение выбранных параметров инструмента
    printMarketMenu(markets);
    return 0;