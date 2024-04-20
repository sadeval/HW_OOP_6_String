#include <iostream>
#include <cstring>
#include <cctype>
#include <locale>

using namespace std;

class String {
    char* text = nullptr;
    char* originalText = nullptr; // Переменная для хранения исходной строки
    unsigned int length = 0;
    unsigned int capacity = 80;

public:
    String() : String("", 80) {}

    String(const char* text) : String(text, 80) {}

    String(unsigned int capacity) : String("", capacity) {}

    String(const String& original) : String(original.text, original.capacity) {}

    String(const char* text, unsigned int capacity) {
        SetString(text, capacity);
    }

    ~String() {
        if (text != nullptr) {
            delete[] text;
            text = nullptr;
        }
        if (originalText != nullptr) {
            delete[] originalText;
            originalText = nullptr;
        }
    }

    void SetString(const char* text, unsigned int capacity = 80) {
        length = strlen(text);

        if (capacity <= length)
            capacity = length + 1;
        this->capacity = capacity;

        delete[] this->text;
        delete[] this->originalText;
        this->text = new char[capacity];
        this->originalText = new char[capacity]; // Создаем память для исходной строки
        strcpy_s(this->text, length + 1, text);
        strcpy_s(this->originalText, length + 1, text); // Копируем переданный текст в исходную строку
    }

    int GetLength() const {
        return length;
    }

    int GetCapacity() const {
        return capacity;
    }

    char GetCharAt(unsigned int index) const {
        if (index < length) {
            return text[index];
        }
        else {
            return text[0];
        }
    }

    void PrintLn() const {
        cout << text << "\n";
    }

    void GetLine() {
        char temp[80];
        cin.getline(temp, 80);
        SetString(temp);
    }

    void Replace(char oldChar, char newChar) {
        for (int i = 0; i < length; i++) {
            if (text[i] == oldChar) {
                text[i] = newChar;
            }
        }
    }

    void Reverse() {
        int i = 0;
        int j = length - 1;
        while (i < j) {
            char temp = text[i];
            text[i] = text[j];
            text[j] = temp;
            i++;
            j--;
        }
    }

    void Concat(const String& another) {
        unsigned int newLength = length + another.length;
        if (newLength + 1 > capacity) {
            capacity = newLength + 1;
            char* newText = new char[capacity];
            strcpy_s(newText, capacity, text);
            strcat_s(newText, capacity, another.text);
            delete[] text;
            text = newText;
        }
        else {
            strcat_s(text, capacity, another.text);
        }
        length = newLength;
    }

    void Shuffle() {
        srand(time(nullptr));
        for (int i = length - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            char temp = text[i];
            text[i] = text[j];
            text[j] = temp;
        }
    }

    void ToUpper() {
        for (int i = 0; i < length; i++) {
            text[i] = toupper(text[i], locale("ru_RU.UTF-8"));
        }
    }
    void RestoreOriginal() {
        strcpy_s(text, capacity, originalText);
    }
};

int main() {
    
    setlocale(0, "Russian");
 
    String replace = "Soon";
    replace.Replace('S', 'M');
    replace.PrintLn();

    String concA("\nI love ");
    String concB("my cats");
    concA.Concat(concB);
    concA.PrintLn();

    String str;
    cout << "\nEnter a string: " << "\n";
    str.GetLine();

    str.ToUpper();
    cout << "After conversion to upper case: " << "\n";
    str.PrintLn();
    str.RestoreOriginal();

    cout << "Original string: " << "\n";
    str.PrintLn();
    cout << "Reversed string: " << "\n";
    str.Reverse();
    str.PrintLn();

    cout << "Shuffled string: " << "\n";
    str.Shuffle();
    str.PrintLn();

}

