
#include "TMonom.h"
#include "TPolinom.h"
#include "MyList.h"
#include "TArithmetic.h"
#include <ctime>
int main() 
{
	std::string name_of_table = "prosmotr_table"; // Выбор таблицы для поиска
	Arithmetic<std::string, TPolinom> arithmetic("pol10=12x^2y^2z^1-2x^1");
	arithmetic.SetTableName(name_of_table);
	// Консольная проверка работы программы
	/*std::string pol1 = "";
	std::string pol2 = "";
	std::string calc = "";

	std::cout << "Polinom1: ";
	std::cin >> pol1;
	std::cout << "Polinom2: ";
	std::cin >> pol2;
	std::cout << "Operation: ";
	std::cin >> calc;

	arithmetic.AddPolinom(pol1);
	arithmetic.AddPolinom(pol2);
	arithmetic.CalculatePolynoms(calc);
	TPolinom p = arithmetic.GetVal("pol3");
	std::cout << "Result:" << "\n" << p;*/

	// Добавляем полиномы в таблицу
	arithmetic.AddPolinom("pol19=2x^2y^2z^1+2x^2+3");
	arithmetic.AddPolinom("pol7=2x^2y^2+2x^2");
	arithmetic.AddPolinom("pol15=2x^2y^1+2x^2-3x^1");
	arithmetic.AddPolinom("pol20=2x^2+2x^1");
	arithmetic.AddPolinom("pol1=2x^2");

	// Считаем полиномы
	arithmetic.CalculatePolynoms("pol11=pol19+pol7");
	arithmetic.CalculatePolynoms("pol3=2pol10-pol7");
	arithmetic.CalculatePolynoms("pol22=2pol11-pol3");
	arithmetic.CalculatePolynoms("pol14=pol22+pol3");
	arithmetic.CalculatePolynoms("pol2=pol20+pol3");
	arithmetic.CalculatePolynoms("pol5=pol1-pol20-pol14");
	arithmetic.CalculatePolynoms("pol23=pol1*pol1");
	arithmetic.CalculatePolynoms("pol13=3pol10-pol1");
	/*arithmetic.CalculatePolynoms("pol55=pol20*pol7");
	arithmetic.CalculatePolynoms("pol82=11pol10+pol22");
	arithmetic.CalculatePolynoms("pol41=pol15-pol7");
	arithmetic.CalculatePolynoms("pol99=pol1*pol22");
	arithmetic.CalculatePolynoms("pol67=9pol20+pol41*pol3");
	arithmetic.CalculatePolynoms("pol26=pol20-8pol1*pol19");
	arithmetic.CalculatePolynoms("pol78=pol15*pol3+pol5");
	arithmetic.CalculatePolynoms("pol50=2pol14-pol1");
	arithmetic.CalculatePolynoms("pol64=pol82-3pol99");
	arithmetic.CalculatePolynoms("pol36=2pol5+pol7*pol3");
	arithmetic.CalculatePolynoms("pol87=pol26+12pol2-pol5");
	arithmetic.CalculatePolynoms("pol56=pol22*pol7+6pol20");
	arithmetic.CalculatePolynoms("pol71=pol2-pol7");
	arithmetic.CalculatePolynoms("pol72=6pol10*pol19*pol1");
	arithmetic.CalculatePolynoms("pol92=pol7+pol14");
	arithmetic.CalculatePolynoms("pol33=3pol71-pol23");
	arithmetic.CalculatePolynoms("pol49=pol19*pol10");
	arithmetic.CalculatePolynoms("pol18=pol99+pol23");
	arithmetic.CalculatePolynoms("pol51=pol82+pol7-pol1");
	arithmetic.CalculatePolynoms("pol61=pol3-pol13*pol36");
	arithmetic.CalculatePolynoms("pol37=4pol71-pol22");
	arithmetic.CalculatePolynoms("pol66=pol2*pol5");
	arithmetic.CalculatePolynoms("pol38=7pol71+pol64");
	arithmetic.CalculatePolynoms("pol45=pol13-pol1");
	arithmetic.CalculatePolynoms("pol4=pol5+pol13");
	arithmetic.CalculatePolynoms("pol34=6pol10-pol19");
	arithmetic.CalculatePolynoms("pol53=2pol36+pol3");
	arithmetic.CalculatePolynoms("pol84=pol1*pol3");
	arithmetic.CalculatePolynoms("pol73=pol67+pol99");
	arithmetic.CalculatePolynoms("pol96=pol3+pol20-pol14");
	arithmetic.CalculatePolynoms("pol76=pol1-pol7*pol5");
	arithmetic.CalculatePolynoms("pol94=3pol1-pol15");
	arithmetic.CalculatePolynoms("pol59=pol20*pol49");
	arithmetic.CalculatePolynoms("pol98=11pol10+pol22");
	arithmetic.CalculatePolynoms("pol75=pol15-pol7");
	arithmetic.CalculatePolynoms("pol47=pol1*pol22");
	arithmetic.CalculatePolynoms("pol63=9pol94+pol41*pol4");
	arithmetic.CalculatePolynoms("pol52=pol20-8pol1*pol19");
	arithmetic.CalculatePolynoms("pol85=pol15*pol3+pol5");
	arithmetic.CalculatePolynoms("pol43=2pol14-pol1");
	arithmetic.CalculatePolynoms("pol28=pol82-3pol75");
	arithmetic.CalculatePolynoms("pol97=2pol5+pol7*pol3");
	arithmetic.CalculatePolynoms("pol35=pol26+12pol2-pol5");
	arithmetic.CalculatePolynoms("pol27=pol22*pol7+6pol20");
	arithmetic.CalculatePolynoms("pol74=pol76-pol35");
	arithmetic.CalculatePolynoms("pol32=6pol47*pol19*pol63");
	arithmetic.CalculatePolynoms("pol95=pol7+pol14");
	arithmetic.CalculatePolynoms("pol25=3pol28-pol63");
	arithmetic.CalculatePolynoms("pol9=pol19*pol10");
	arithmetic.CalculatePolynoms("pol8=pol99+pol23");
	arithmetic.CalculatePolynoms("pol54=pol82+pol7-pol1");
	arithmetic.CalculatePolynoms("pol86=pol3-pol94*pol9");
	arithmetic.CalculatePolynoms("pol69=4pol71-pol22");
	arithmetic.CalculatePolynoms("pol80=pol2*pol5");
	arithmetic.CalculatePolynoms("pol70=7pol71+pol64");
	arithmetic.CalculatePolynoms("pol39=pol70-pol1");
	arithmetic.CalculatePolynoms("pol58=pol15*pol3+pol5");
	arithmetic.CalculatePolynoms("pol17=2pol32-pol1");
	arithmetic.CalculatePolynoms("pol65=pol50-3pol75");
	arithmetic.CalculatePolynoms("pol90=2pol5+pol8*pol3");
	arithmetic.CalculatePolynoms("pol93=pol26+12pol2-pol5");
	arithmetic.CalculatePolynoms("pol12=pol22*pol7+6pol20");
	arithmetic.CalculatePolynoms("pol81=pol76-pol35");
	arithmetic.CalculatePolynoms("pol16=6pol47*pol19*pol63");
	arithmetic.CalculatePolynoms("pol88=pol7+pol14");
	arithmetic.CalculatePolynoms("pol48=3pol28-pol63");
	arithmetic.CalculatePolynoms("pol30=pol19*pol10");
	arithmetic.CalculatePolynoms("pol29=pol99+pol23");
	arithmetic.CalculatePolynoms("pol40=pol82+pol7-pol1");
	arithmetic.CalculatePolynoms("pol24=pol3-pol94*pol9");
	arithmetic.CalculatePolynoms("pol21=4pol71-pol22");
	arithmetic.CalculatePolynoms("pol31=pol2*pol5");
	arithmetic.CalculatePolynoms("pol42=7pol71+pol64");
	arithmetic.CalculatePolynoms("pol44=pol70-pol1");
	arithmetic.CalculatePolynoms("pol83=pol44+11pol14");
	arithmetic.CalculatePolynoms("pol57=3pol28-pol63");
	arithmetic.CalculatePolynoms("pol68=pol19*pol10");
	arithmetic.CalculatePolynoms("pol46=pol99+pol23");
	arithmetic.CalculatePolynoms("pol77=pol82+pol7-pol1");
	arithmetic.CalculatePolynoms("pol89=pol3-pol94*pol9");
	arithmetic.CalculatePolynoms("pol79=4pol71-pol22");
	arithmetic.CalculatePolynoms("pol62=pol2*pol5");
	arithmetic.CalculatePolynoms("pol60=7pol71+pol64");
	arithmetic.CalculatePolynoms("pol91=pol70-pol1");
	arithmetic.CalculatePolynoms("pol6=12pol71*pol68");
	arithmetic.CalculatePolynoms("pol100=3pol70-pol60");
	*/
	cout << "runtime = " << clock() / 1000.0 << endl;
	return 0;
}