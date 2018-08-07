#include "ncorp.h"
#include <math.h>
#include <limits>
#include <deque>


static unsigned usqrt4(unsigned val)
{
    unsigned a, b;
    if (val < 2) return val; /* avoid div/0 */
    a = 1255;       
    b = val / a; a = (a+b) /2;
    b = val / a; a = (a+b) /2;
    b = val / a; a = (a+b) /2;
    b = val / a; a = (a+b) /2;
    return a;
}
//////////////////////////////////////////////////////

//информация о генах
GEN_INFO OECOSYS::genes[N_GENES];

//вклад видовой части генов
unsigned char CORP::spe_gen_part = 16;

//способ передачи генов от родителя к потомку
CORP::MODUS_REPLICANDI CORP::modus_replicandi = CORP::CRUCI;

// вероятность случайной мутации
float CORP::mutationis_probabilitas = 0.01;

///////////////////////////////////////////////////////

//полное значение фенотипического параметра
float CORP::phaeno(int p) { return OECOSYS::genes[p].val(this); }

CORP::CORP()
{
	//нулевое ускорение
	ax = 0;
	ay = 0;

	//массивность
	m = 0;

	// жизненные силы
	e = m;

	//эффективность существования
	v = 0;			// время жизни
	ndevor = 0;		// количество съеденных
	ngen = 0;		// количество рожденных

	//поколение
	gener = 0;

	//пустые гены
	erase();

	est = false;
	vic = 0;		// номер существа, с которым назначено взаимодействие
}


//=========================================================================================================
// генерация по прямым генам 
//=========================================================================================================
CORP::CORP(GENE g1, GENE g2):gen_spe(g1),gen_ind(g2)
{
	//нулевое ускорение
	ax = 0;
	ay = 0;

	//массивность
	m = phaeno (MIN_REPRODUCT_MASS) / 2;

	// жизненные силы
	e = m;

	//эффективность существования
	v = 0;			// время жизни
	ndevor = 0;		// количество съеденных
	ngen = 0;		// количество рожденных

	//поколение
	gener = 0;

	est = true;
	vic = 0;		// номер существа, с которым назначено взаимодействие
}

//=========================================================================================================
//порождение половым способом
//=========================================================================================================
CORP::CORP( CORP& parent1, CORP& parent2)
{
	gen_spe = parent1.gen_spe;

	gen_ind = 0;

	bool casus = (rand() > rand());
	for(GENE i=0; i<N_GENES; i++)
	{
		GENE g;
		switch(modus_replicandi)
		{
			case EFFIC: casus = (parent1.effic() > parent2.effic());	break;		//абстрактная эффективность
			case CASUAL: casus = casus;									break;		//случайный из пары родителей
			case CRUCI: casus = (rand() > rand());						break;		//кроссинговер
		}
			
		g = casus	? parent1.gen_ind : parent2.gen_ind;
		GENE rna = synth (g, i*4+3, i*4);
		if(rand() < mutationFreq()*RAND_MAX) rna = rand()&15;
		gen_ind = gen_ind | (rna<<(i*4));
	}

	//позиция
	x = (parent1.x + parent2.x)/2; rx = x + 0.02;
	y = (parent1.y + parent2.y)/2; ry = y + 0.02;

	//нулевое ускорение
	ax = 0;
	ay = 0;

	//отнятие массы у родителей
	m = (parent1.m + parent2.m)/2;
	parent1.m/=2; parent2.m/=2;
	e = m;

	//эффективность существования
	v = 0;			// время жизни
	ndevor = 0;		// количество съеденных
	ngen = 0;		// количество рожденных

	//поколение
	gener = (parent1.gener>parent2.gener ? parent1.gener : parent2.gener)+1;

	//жив
	est = true;
	vic = 0;		// номер существа, с которым назначено взаимодействие
}



