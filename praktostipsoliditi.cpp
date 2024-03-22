#include <iostream>
#include <locale>
#include <Windows.h>
#pragma execution_character_set("utf-8")
using namespace std;

class BankAccount {
private:
    int accountNumber; // Номер банковского счета
    double balance; // Баланс
    double interestRate; // Процентная ставка

    // Рассчет процентов
    double calcInterest() const {
        return balance * interestRate * (1.0 / 12);
    }

public:
    // Конструктор с начальным балансом
    BankAccount(int accNumber, double initialBalance, double Percent)
        : accountNumber(accNumber), balance(initialBalance), interestRate(Percent) {}

    // Внести средства на счет
    void deposit(double summ) {
        balance += summ;
    }

    // Снять средства со счета
    void withdraw(double summ) {
        if (balance >= summ) {
            balance -= summ;
        }
        else {
            cout << "Ошибка: Недостаточно средств" << endl;
        }
    }

    // Получить текущий баланс
    double getBalance() const {
        return balance;
    }

    // Получить сумму процентов
    double getInterest() const {
        return calcInterest();
    }

    // Обновить процентную ставку
    void setInterestRate(double newRate) {
        this->interestRate = newRate;
    }

    // Получить номер банковского счета
    int getAccountNumber() const {
        return this->accountNumber;
    }

    // Дружественная функция для трансфера (перевода средств)
    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

// Функция для трансфера
bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (from.balance >= amount) {
        from.withdraw(amount);
        to.deposit(amount);
        return true;
    }
    else {
        cout << "Ошибка: Недостаточно средств для перевода" << endl;
        return false;
    }
}

int main() {
    SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8
    SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8
    double balanceAcc1, balanceAcc2;
    int acc1, acc2;
    double interestRate{};

    // Ввод информации для первого аккаунта
    cout << "Введите номер счета для первого аккаунта: ";
    while (!(cin >> acc1) || acc1 <= 0) {
        cout << "Ошибка: Введите целое положительное число для номера счета!" << endl;
        cout << "Введите номер счета для первого аккаунта: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Введите начальный баланс для первого аккаунта: $";
    while (!(cin >> balanceAcc1) || balanceAcc1 < 0) {
        cout << "Ошибка: Введите положительное число для начального баланса!" << endl;
        cout << "Введите начальный баланс для первого аккаунта: $";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // Ввод информации для второго аккаунта
    cout << "Введите номер счета для второго аккаунта: ";
    while (!(cin >> acc2) || acc2 <= 0 || acc2 == acc1) {
        cout << "Ошибка: Введите уникальное целое положительное число для номера счета!" << endl;
        cout << "Введите номер счета для второго аккаунта: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Введите начальный баланс для второго аккаунта: $";
    while (!(cin >> balanceAcc2) || balanceAcc2 < 0) {
        cout << "Ошибка: Введите положительное число для начального баланса!" << endl;
        cout << "Введите начальный баланс для второго аккаунта: $";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    BankAccount account1(acc1, balanceAcc1, interestRate);
    BankAccount account2(acc2, balanceAcc2, interestRate);

    cout << "Начальный баланс в аккаунте 1: $" << account1.getBalance() << endl;
    cout << "Начальный баланс в аккаунте 2: $" << account2.getBalance() << endl;

    double transferAmount;
    cout << "Введите сумму перевода: $";
    while (!(cin >> transferAmount) || transferAmount <= 0) {
        cout << "Ошибка: Введите положительное число для суммы перевода!" << endl;
        cout << "Введите сумму перевода: $";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Введите процентную ставку: ";
    while (!(cin >> interestRate) || interestRate < 0) {
        cout << "Ошибка: Введите положительное число для процентной ставки!" << endl;
        cout << "Введите процентную ставку: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (transfer(account1, account2, transferAmount)) {
        cout << "Перевод успешен!" << endl;
    }

    cout << "Конечный баланс в аккаунте 1: $" << account1.getBalance() << endl;
    cout << "Конечный баланс в аккаунте 2: $" << account2.getBalance() << endl;

    account1.setInterestRate(interestRate);
    account2.setInterestRate(interestRate);

    cout << "Проценты на аккаунте 1: $" << account1.getInterest() << endl;
    cout << "Проценты на аккаунте 2: $" << account2.getInterest() << endl;

    return 0;
}
