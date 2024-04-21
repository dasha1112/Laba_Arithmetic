#ifndef _ARITHMETIC_
#define _ARITHMETIC_
#include "TVector.h"
#include "MyList.h"
#include "TPolinom.h"
#include "HashTable.h"
#include "TSortTable.h"
#include "TTable.h"
#include "TTree.h"
#include "TMonom.h"
#include "TNode.h"
#include "TStack.h"
#include <iostream>
#include <algorithm>

template <class TKEY, class TVAL>
class Arithmetic
{
protected:
  TTable<std::string, TPolinom>* prosmotr_table;
  TSortTable<std::string, TPolinom>* sort_table;
  THashTable<std::string, TPolinom>* hash_table;
  TTreeTable<std::string, TPolinom>* tree_table;
  std::string str;
  std::string name_table;
public:
  Arithmetic(std::string s = "");
  ~Arithmetic();

  void SetTableName(std::string s);
  TPolinom GetVal(TKEY k);
  TPolinom Execute(char op, TPolinom first, TPolinom second);
  int Priority(char c);
  void AddPolinom(std::string s);
  std::string ToPostfix(std::string infixExpr);
  void CalculatePolynoms(std::string s);
  void AddToTables(std::string name, TPolinom p);
  TPolinom Split();
  std::string GetKeyName();
};

template<class TKEY, class TVAL>
inline Arithmetic<TKEY, TVAL>::Arithmetic(std::string s)
{
  str = s;
  prosmotr_table = new TTable<std::string, TPolinom>(); // Инициализация объектов таблиц
  sort_table = new TSortTable<std::string, TPolinom>();
  hash_table = new THashTable<std::string, TPolinom>();
  tree_table = new TTreeTable<std::string, TPolinom>();
  if (str != "") 
  {
    std::string keyName = GetKeyName(); // Получаем ключ для таблиц
    TPolinom p = Split(); // Получаем значения для таблиц
    AddToTables(keyName, p);
  }
}

template<class TKEY, class TVAL>
inline Arithmetic<TKEY, TVAL>::~Arithmetic()
{
}


template<class TKEY, class TVAL>
inline void Arithmetic<TKEY, TVAL>::SetTableName(std::string s)
{
  name_table = s;
}

template<class TKEY, class TVAL>
inline TPolinom Arithmetic<TKEY, TVAL>::GetVal(TKEY k)
{
  TPolinom p1;
  if (name_table == "hash_table") { p1 = hash_table->Find(k); }
  if (name_table == "tree_table") { p1 = tree_table->Find(k); }
  if (name_table == "sort_table") { p1 = sort_table->Find(k); }
  if (name_table == "prosmotr_table") { p1 = prosmotr_table->Find(k); }
  return p1;
}

template<class TKEY, class TVAL>
inline TPolinom Arithmetic<TKEY, TVAL>::Execute(char op, TPolinom first, TPolinom second)
{
  if (op == '+') { return first + second; }
  if (op == '-') { return first - second; }
  if(op == '*') { return first * second; }
}

template<class TKEY, class TVAL>
inline int Arithmetic<TKEY, TVAL>::Priority(char c)
{
  if (c == '+' || c == '-') return 1;
  else if (c == '*') return 2;
  return 0;
}

template<class TKEY, class TVAL>
inline void Arithmetic<TKEY, TVAL>::AddPolinom(std::string s)
{
  str = s;
  std::string keyName = GetKeyName(); // Получаем ключ для таблиц
  TPolinom p = Split(); // Получаем значения для таблиц
  AddToTables(keyName, p);
}

template<class TKEY, class TVAL>
inline std::string Arithmetic<TKEY, TVAL>::ToPostfix(std::string infixExpr)
{
  std::string postfixExpr = ""; // Постфиксная строка
  std::string name_pol = ""; // Строка имени полинома (ключа)
  bool num = true; // Флаг, что элемент это число
  int index_word = 0;

  TStack<char> stack(infixExpr.size());
  for (int i = 0; i < infixExpr.size(); i++)
  {
    char c = infixExpr[i];

    if(isdigit(c) && num == true)
    {
      postfixExpr += c;
      num = true;;
    }
    else if (!isdigit(c) && num == true) { num = false; }

    if(c != '+' && c != '-' && c != '*' && c != '\0' && num == false) // Находим название (ключ) полинома
    {
      postfixExpr += c;
      index_word++;
    }

    if (c == '*' || c == '+' || c == '-')
    {
      postfixExpr += " ";
      num = true;
      index_word = 0;
      while (stack.GetCount() > 0 && Priority(stack.Top()) >= Priority(c))
      {
        postfixExpr += stack.GetElem();
      }
      stack.Push(c);
    }
  }
  while (stack.GetCount() > 0)
  {
    postfixExpr += " ";
    postfixExpr += stack.GetElem();
  }
  return postfixExpr;
}

template<class TKEY, class TVAL>
inline void Arithmetic<TKEY, TVAL>::CalculatePolynoms(std::string stroka)
{
  str = stroka;
  std::string keyName = GetKeyName(); // Получили ключ
  std::string str1 = ToPostfix(str);
  int i = 0;
  const char* s = str1.c_str();
  int length = strlen(s);
  bool flag = true;
  TStack<TPolinom> stack(length);
  
  while (i < length) 
  {
    TPolinom p1;
    TPolinom p2;

    std::string name = "";
    double coefficient = 1.0;
    int j = 0;

    while (isdigit(s[i]) && flag == true) // Если перед пеолиномом число, то сохраняем его
    {
      if (!isdigit(s[i + 1])) 
      { 
        flag = false; 
        coefficient = atof(&s[i-j]);
      }
      j++;
      i++;
    }

    while (s[i] != ' ' && s[i] != '\0')  // Находим название (ключ) полинома
    {
      name += s[i];
      i++;
    }

    if (name != "") 
    {
      flag = true;
      if (name_table == "hash_table"){ p1 = hash_table->Find(name); }
      if (name_table == "tree_table") { p1 = tree_table->Find(name); }
      if (name_table == "sort_table") { p1 = sort_table->Find(name); }
      if (name_table == "prosmotr_table") { p1 = prosmotr_table->Find(name); }
      p2 = p1 * coefficient; // Умножаем на константу
      stack.Push(p2);
    }
  
    i++;
    if (s[i] == '+' || s[i] == '-' || s[i] == '*') //Если операция
    {
      TPolinom second = stack.GetElem();
      TPolinom firrst = stack.GetElem();
      TPolinom result = Execute(s[i], firrst, second);
      stack.Push(result);  
      i++;
    }

  }
  TPolinom finalresult = stack.Top();
  AddToTables(keyName, finalresult);
}


template<class TKEY, class TVAL>
inline void Arithmetic<TKEY, TVAL>::AddToTables(std::string name, TPolinom p)
{
  prosmotr_table->Push(name, p);
  sort_table->Push(name, p);
  tree_table->Add(new std::string(name), new TPolinom(p));
  hash_table->Add(&name, &p);
  std::cout << "Key: " << name << " " <<"Polynom: " << p << "\n";
}

template<class TKEY, class TVAL>
inline TPolinom Arithmetic<TKEY, TVAL>::Split()
{
  TPolinom polinom;
  int i = 0;
  const char* s = str.c_str();
  int length = strlen(s);
  bool flag = true;

  while (i <= length) 
  {
      TMonom* m = new TMonom();
      double coefficient = 1.0;
      while (isdigit(s[i]) && flag == true)
      {
        coefficient = atof(&s[i]);
        i++;
        flag = false;
      }

      // Находим степени
      TVector<double> degrees;
      while (s[i] != '+' && s[i] != '-' && s[i] != '\0')
      {
        if (s[i] != '\0' && isalpha(s[i]))  // Проверяем наличие переменной
        {
          char variable = s[i];
          i++; // Переходим к следующему символу
          if (s[i] == '^' && isdigit(s[i + 1])) // Проверяем наличие степени после ^
          {
            i++;
            double power = atof(&s[i]);
            degrees.Push(power);
          }
          else
          {
            degrees.Push(0.0); // Если степень не указана, считаем ее равной 0
          }
        }
        i++;
      }

    m->SetC(coefficient);
    m->SetDegrees(degrees);
    polinom += *m;
    i++;
    flag = true;
  }

  return polinom;
}


template<class TKEY, class TVAL>
inline std::string Arithmetic<TKEY, TVAL>::GetKeyName()
{
  std::string name;
  size_t equalPos = str.find("=");

  if (equalPos != std::string::npos) {
    // Извлечь слово "pol" (перед "=")
    name = str.substr(0, equalPos);

    // Удалить "до" и "ровно", оставив часть после "="
    str.erase(0, equalPos + 1);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // удалить все пробелы
  }
  return name;
}

#endif