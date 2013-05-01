

#include "cell.h"
#include <iostream>

using namespace std;

main()
{

Cell a;


a.eliminate(1);
a.eliminate(2);
a.eliminate(3);
a.eliminate(4);
a.eliminate(5);
a.eliminate(6);
a.eliminate(7);
a.eliminate(8);


for(int i = 1 ; i < 10 ; i++)
{

cout << a.possibility(i) << endl;

}


cout << a.probability(1) << endl;
cout << a.probability(9) << endl;



}
