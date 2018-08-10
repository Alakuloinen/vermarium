#pragma once
#include <list>
#include <deque>
#include <vector>
#include <cstdint>
#include <ctime>

typedef uint64_t GENE;
#define DEGENE 0xffffffffffffffff

//заполнить ген произвольными последовательностями
inline GENE stoch() { return ((GENE)rand()<<56) + ((GENE)rand()<<48) + ((GENE)rand()<<40) + ((GENE)rand()<<32) + ((GENE)rand()<<24) + ((GENE)rand()<<16) + ((GENE)rand()<<8) + ((GENE)rand()) ; }

inline float rndb() {return ((float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX); }
inline float rndu() {return (float)rand()/(float)RAND_MAX; }

#define DECL_GEN_STR(x) #x


//фенотипические характеристики
enum PHAENO
{ 
	SUI_PHILIA,
	SUI_PHOBIA,					// сила сближения и удаления к своим
	OPP_PHILIA,
	OPP_PHOBIA,					// сила сближения и удаления к чужим
	STOCH_MOT_INTENT,				// коэффициент случайного движения
	TEMP_VIRGIN,				// уменьшение случайного движения при соседях
	OPT_VIC_NUM,					// оптимальное число соседей
	MIN_REPRODUCT_MASS,				// минимальная общая массивность, с которой влкючается половое поведение
	MAX_DIST_VIS,				// расстояние видимости
	MAX_DIST_ACT,				// расстояние видимости

	MAX_DIST_DEVOR,					// расстояние резульативной атаки
	MAX_DIST_FUCK,					// расстояние резульативного оплодотворения

	PAEDOPHILIA,					// приближение к своим, даже если они еще не достигли репродуктивной массы
	NECROPHAGIA,					// падальщичество

	MAX_MASS,						// максимальная масса

	TEMPUS_VITAE,					// время жизни

	N_GENES
};


struct CORP
{
	friend class OECOSYS;

	enum MODUS_REPLICANDI { EFFIC, CASUAL, CRUCI };

	/////////////////////////////////////////////

	//гены
	GENE gen_spe;			// видовая часть генов
	GENE gen_ind;			// индивидуальная часть генов

	//общие
	float e;				// жизненные силы
	float m;				// массивность

	//кинематика
	float x;	float y;	// позиция
	float rx;	float ry;	// позиция ранее
	float ax;	float ay;	// ускорение/намерение

	//статистика
	float v;				// время жизни
	float d;				// расстояние, пройденное к текущему времени
	unsigned long ndevor;	// количество съеденных
	unsigned long ngen;		// количество рожденных
	unsigned long gener;	// поколение

	//служебные
	bool est;				// в принципе существует ли

	/////////////////////////////////////////////

	static MODUS_REPLICANDI modus_replicandi;	// способ передачи генов от родителя к потомку
	static unsigned char spe_gen_part;			// вклад видовой части генов
	static float mutationis_probabilitas;		// вероятность случайной мутации
	static float species_mutatio;				// мутировать также и виды

	/////////////////////////////////////////////

	// существо, с которым назначено взаимодействие. 
	CORP* vic;				

	// получить фенотипическую характеристику целую
	int phaeno_int( PHAENO p )		const {	return	synth (gen_spe, p*4+3, p*4) * spe_gen_part + 
												synth (gen_ind, p*4+3, p*4) * (17-spe_gen_part);	}

	//получить фенотипическую характеристику в диапазоне  0 1
	float phaeno_uni( PHAENO p )	const {	return (float)( phaeno_int(p) )/255.0;	}

	//получить фенотипическую характеристику в диапазоне -1 1
	float phaeno_bip( PHAENO p )	const {	return (float)( phaeno_int(p) )/127.0 - 1.0;	}

	//показатель эффективности, пока не используется
	unsigned long effic()			const {	return (v + ngen + ndevor)/3;}

	//отпущенное время жизни зависит от генов явно и деяний хз как
	float limit()					const {	return (0.5 + phaeno_uni(TEMPUS_VITAE)) + 0.025*(gen_ind%20); }

	//законченный фенотипический показатель
	float phaeno (int p);

	//стереть генетическую информацию
	void erase()
	{
		gen_spe = DEGENE;
		gen_ind = DEGENE;
	}

	//быстрое расстояние по восьмиграннику
	float dist(CORP& o)
	{ 
		float x1 = fabs(x-o.x);
		float y1 = fabs(y-o.y);
		return (x1 + y1 + (x1>y1?x1:y1))/2;
	}

	//убить и съесть
	void devor(CORP& vic, float crit_dist)
	{

		//не влезает
		if(m + vic.m > phaeno(MAX_MASS))
		{
			return;
		}
		
		//присвоить чужую массу
		m += vic.m; 

		//если съел труп, энергия сразу в максимум, иначе может резко опуститься
		e = e - vic.e;
		vic.e = 0;						
		vic.erase();
		vic.m = 0;
		ndevor++;
	}

	bool operator==(const CORP& o) { return o.gen_ind==gen_ind; }
	bool operator!=(const CORP& o) { return o.gen_ind!=gen_ind; }

	bool mortuus ()			{ return (e<=0); }
	bool vanus ()			{ return (mortuus() && m<=0); }
	bool vivus ()			{ return (est && e>0 && m>0); }
	bool rasus ()			{ return (gen_spe == DEGENE && gen_ind == DEGENE); }



	CORP();

	// генерация по прямым генам 
	CORP(GENE g1, GENE g2);

	//порождение половым способом
	CORP( CORP& parent1, CORP& parent2);

	// способ передачи генов от родителя к потомку
	static const MODUS_REPLICANDI	modusReplicandi ()						{ return modus_replicandi; }
	static void						modusReplicandi (MODUS_REPLICANDI mr)	{  modus_replicandi = mr; }

	// вклад видовой части генов
	static const unsigned char		specGenImpact ()						{ return spe_gen_part; }
	static void						specGenImpact (unsigned char val)		{  spe_gen_part = val%17; }

	// вероятность случайной мутации
	static const float				mutationFreq ()							{ return mutationis_probabilitas; }
	static void						mutationFreq (float val)				{  mutationis_probabilitas = (val>=0.0&&val<=1.0)?val:0.01; }

	// мутировать также и виды
	static const float				mutSpecies ()							{ return species_mutatio; }
	static void						mutSpecies (float val)					{  species_mutatio = (val>=0.0&&val<=1.0)?val:0.01; }

	//синтезировать значение гена
	static unsigned int synth (GENE g, int l, int r ) { return (g>>r) & (~(0xffffffff<<(l-r+1))); }

};


//№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
//№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
//информация о каждом гене
struct GEN_INFO
{
	PHAENO phaeno;
	float praesum;
	float multip;
	char* nomen;
	GEN_INFO():nomen(""),praesum(0),multip(0),phaeno(N_GENES) {}
	GEN_INFO(char *nm, PHAENO p, float s, float m):nomen(nm),praesum(s),multip(m),phaeno(p) {}
	inline float val(CORP* ind) { return praesum + multip*ind->phaeno_uni(phaeno); }
	void synth(CORP* ind, float val)
	{ 
		float r = ((val - praesum)/multip);
		GENE rs = (r/17)*CORP::specGenImpact();
		GENE ri = (r/17)*(17-CORP::specGenImpact());
		ind->gen_ind = ind->gen_ind | (rs<<(phaeno*4));
	}
};

//№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
struct SPE_STAT
{
	GENE g;
	int qnt;
	float m;
	SPE_STAT():m(0),qnt(0),g(DEGENE) {}
};


//№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
class OECOSYS
{
	friend class CORP;

public:

	std::list<SPE_STAT> species;	// список видов
	std::vector <CORP> corp;		// список тел

private:
	//ограничители
	float lx1; float ly1; float lx2; float ly2;

	CORP *sel;				// выделенный

	float massa;			// вся масса
	float frictio;			// глобальная сила трения
	float tempus_mortis;	// глобальное среднее время жизни
	int vivi;				// число настоящих живых
	int gener;				// максимальное поколение
	bool agit;				// работает
	CORP* ultvid;			// индекс последнего удаленного
	bool incestus;			// возможен ли инцест

	uint64_t tacta;			// счетчик тактов
	uint64_t tc;			// время в наносекундах
	double dt;				// промежуток времени текущего такта
	double pr_dt;			// промежуток времени предыдущего такта
	float min_dt;			// минимальная дельта, для пропуска тактов
	float max_dt;			// максимальная дельта, для пропуска тактов
	
	double global_factor;	// множитель для регуляции скорости

	///////////////////////////////////////////////////////////////
	
	static GEN_INFO genes[N_GENES];//фенотипические характнристики генов


public:


	//количество существ
	int n() const { return corp.size(); }

	//конструктор по ограничительному прямоугольнику
	OECOSYS(float x1, float y1, float x2, float y2);
	OECOSYS(std::string arch);
	void arch(std::string &dst);
	~OECOSYS();

	//породить экосистему
	void gen(int n, int nsp, int pattern = 0);

	//добавить тучку существ нового вида
	void add(GENE spec, int n, float x, float y, float distr);

	//родить и убить 
	void corp_gen (CORP& p1, CORP& p2);
	void corp_nec (CORP& c);

	//вычислить один шаг для отдельно взятого
	void mod_a (CORP& cur);							// динамика + планы на роды/смерть
	void mod_s (CORP& cur);							// родить/убить
	void mod_r (CORP& cur, double dT, double pdT);	// кинематика, верле

	//вычислить один шаг для интервала или для всех сразу
	void mod_ra (int a, int b);		// динамика и планы + кинематика
	void mod_s ();					// родить/убить

	//полный шаг со всем 
	void iteratio(uint64_t nsec);

	//преднастройка шагов времени перед перезапуском
	void presync(uint64_t nsec = 0) { tc = nsec; pr_dt = min_dt; dt = pr_dt; }

	//подведение итогов шага просчёта, перевычисление интервала времени
	bool synchro_post (uint64_t nsec)
	{ 	
		pr_dt = dt;
		dt = (nsec-tc)*(0.001*0.001);
		if(dt<min_dt)	{	dt = pr_dt;				return false;		}
		else			{	tacta++;	tc = nsec;	return true;		}
	}

	//вычислить статистику
	void calcul();

	//границы
	float lim_x00() const { return lx1; }
	float lim_y00() const { return ly1; }
	float lim_x11() const { return lx2; }
	float lim_y11() const { return ly2; }
	float dim_x() const { return lx2-lx1; }
	float dim_y() const { return ly2-ly1; }

	//возможность спариваться с идентичными
	void incest(bool val) { incestus = val; }
	bool incest() { return incestus; }

	//время жизни
	void longaevitas(float val) { tempus_mortis = val; }
	float longaevitas() { return tempus_mortis; }

	//колво живых
	int populatio() const { return vivi; }

	//биомасса
	float biomassa() const { return massa; }

	//максимальное поколение
	int max_gener() const { return gener; }

	//все мертвы
	bool mort() { return massa == 0; }

	//пуск/стоп
	void cessa() { agit = false; }
	void resume() { agit = true; }
	bool in_actione() const { return agit; }

	//число тактов
	uint64_t gressus() { return tacta; } 

	//выделение
	CORP* selectum() const { return sel; }
	void deselecta() { sel = 0; }
	bool selecta(float x, float y);
//	int sel_species() { if(!sel) return -1; for(int i=0; i<species.size(); i++) if(species[i].g == sel->gen_spe) return i; }

	///////////////////////////////////////////////////////

	static void add_gen(char *nm, PHAENO p, float s, float m){ genes[p] = GEN_INFO(nm,p,s,m); }
	static void init_gen(); //все гены
	static const GEN_INFO gen_info(int i) { return genes[i]; }
};