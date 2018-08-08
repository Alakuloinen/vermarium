#include <sstream>
#include "ncorp.h"


//=========================================================================================================
//конструктор по ограничительному прямоугольнику
//=========================================================================================================
OECOSYS::OECOSYS(float x1, float y1, float x2, float y2) : lx1(x1),lx2(x2),ly1(y1),ly2(y2)
{ 
	//интересные виды

	//17866963036761450694 - активен и умеренно юрок, любит кушать трупы больше, чем секс - побеждает всех ниже описанных
	//1278357829164476668 - эффектен, плодовит, юрок

	//*14720509442452787552 - юрок, среднего размера, не сгибается под 1498, но оба быстро вымирают. с 6668 на равных, но 6668 лучше ест трупы
	//12744507702642470090 - мощен, прямолинеен - побеждает 6668
	//13809298358541492955 - похож, но долгожитель, может пережить атаку 0694

	//8724366813468701498 - мощен, сильно прямолинеен, быстрый охотник но ленивый родитель - побеждает 6668, но не справляется со старостью
	// хорошо атакует 0090, но сдаёт позиции в силу половой ригидности, и 0090 забирает всю падаль

	//9948173688290192475 - непутев, мелок, но плодовит

	//13578888850524779131 - мелок, эффектен в своей трусливости, оттого способен пережить 0694 и навалять в ответ.
	// в пропорциональном методе вообще всех делает, потому что коллективно убегает быстрее всех

	//2173306846711227531 - индивидуализм эскапизм, но крупен и охоч до мелких , интересна борьба с 9131


	//18281394467048421106 пока непонятно

	agit = false;
	global_factor = 0.0004;
	massa = 0;
	sel = 0;
	frictio = 0.02;
	tempus_mortis = 100;
	ultvid = 0;

	tacta=0;
	agit=0;
	ultvid=0;
	tc = 0;

	min_dt = 1.5;
	max_dt = 20;
	dt = min_dt;
	pr_dt = min_dt;

}
OECOSYS::~OECOSYS()
{
}

//=========================================================================================================
//породить из данныx файла
//=========================================================================================================
OECOSYS::OECOSYS(std::string arch)
{
	std::istringstream iss(arch);

	//настройки
	iss.read((char*)&lx1,sizeof(float));
	iss.read((char*)&lx2,sizeof(float));
	iss.read((char*)&ly1,sizeof(float));
	iss.read((char*)&ly2,sizeof(float));
	iss.read((char*)&frictio,sizeof(float));
	iss.read((char*)&global_factor,sizeof(double));
	iss.read((char*)&tacta,sizeof(uint64_t));
	iss.read((char*)&tc,sizeof(uint64_t));
	iss.read((char*)&dt,sizeof(double));
	iss.read((char*)&pr_dt,sizeof(double));
	iss.read((char*)&min_dt,sizeof(float));
	iss.read((char*)&max_dt,sizeof(float));
	iss.read((char*)&incestus,sizeof(bool));
	iss.read((char*)&tempus_mortis,sizeof(float));

	//ссылка на цепь удаленных по индексу
	unsigned short _ultvid;
	iss.read((char*)&_ultvid,sizeof(unsigned short));

	//виды
	unsigned short g;
	iss.read((char*)&g,sizeof(unsigned short));
	for(int i=0;i<g;i++)
	{
		SPE_STAT ss;
		iss.read((char*)&ss, sizeof(SPE_STAT));
		species.push_back(ss);
	}

	//сами существа
	iss.read((char*)&g,sizeof(unsigned short));
	std::vector<unsigned short> refs;
	refs.reserve(g);
	for(int i=0;i<g;i++)
	{
		CORP c(0,0);
		iss.read((char*)&c, sizeof(CORP));
		unsigned short rind;
		iss.read((char*)&rind,sizeof(unsigned short));
		refs.push_back(rind);
		corp.push_back(c);
	}

	//определение ссылок
	if(_ultvid!=0xffff) ultvid = &corp[_ultvid];
	else ultvid = 0;
	for(int i=0;i<g;i++)
	{
		if(refs[i]!=0xffff)
			corp[i].vic = &corp[refs[i]];
		else
			corp[i].vic = 0;
	}
	sel = 0;
	agit = 0;
	calcul();
}

//=========================================================================================================
//сериализовать в строку данных для файла
//=========================================================================================================
void OECOSYS::arch (std::string &dst)
{
	std::ostringstream iss(std::ios::binary);

	//настройки
	iss.write((char*)&lx1,sizeof(float));
	iss.write((char*)&lx2,sizeof(float));
	iss.write((char*)&ly1,sizeof(float));
	iss.write((char*)&ly2,sizeof(float));
	iss.write((char*)&frictio,sizeof(float));
	iss.write((char*)&global_factor,sizeof(double));
	iss.write((char*)&tacta,sizeof(uint64_t));
	iss.write((char*)&tc,sizeof(uint64_t));
	iss.write((char*)&dt,sizeof(double));
	iss.write((char*)&pr_dt,sizeof(double));
	iss.write((char*)&min_dt,sizeof(float));
	iss.write((char*)&max_dt,sizeof(float));
	iss.write((char*)&incestus,sizeof(bool));
	iss.write((char*)&tempus_mortis,sizeof(float));

	//ссылка на цепь удаленных по индексу
	unsigned short _ultvid = ultvid - &corp[0];
	if(ultvid ==0) _ultvid = 0xffff;
	iss.write((char*)&_ultvid,sizeof(unsigned short));

	//виды
	unsigned short g = species.size();
	iss.write((char*)&g,sizeof(unsigned short));
	for(int i=0;i<g;i++)
		iss.write((char*)&species[i], sizeof(SPE_STAT));

	//сами существа
	g = corp.size();
	iss.write((char*)&g,sizeof(unsigned short));
	std::vector<unsigned short> refs;
	refs.reserve(g);
	for(int i=0;i<g;i++)
	{
		refs.push_back(0);
		if(corp[i].vic == 0)
			refs[i] = 0xffff;
		else
			refs[i] = corp[i].vic - &corp[0];

		iss.write((char*)&corp[i], sizeof(CORP));
		iss.write((char*)&refs[i],sizeof(unsigned short));
	}


	dst = iss.str();
}


//=========================================================================================================
//породить эн тел
//=========================================================================================================
void OECOSYS::gen(int n, int nsp, int pattern)
{
	tacta=0;
	agit=0;
	ultvid=0;
	tc = 0;

	min_dt = 1.5;
	max_dt = 20;
	dt = min_dt;
	pr_dt = min_dt;

	//заполнить множество видов произвольно
	for(int i=0; i<nsp; i++)
	{
		SPE_STAT ss;
		ss.g = stoch();
		ss.m = 0;
		ss.qnt = 0;
		species.push_back(ss);
	}

	int storona = sqrt((float)n*nsp);

	corp.reserve(n*nsp);

	//заполнить все существа
	for(int s=0;s<nsp;s++)
	for(int i=0;i<n;i++)
	{
		//образец нового существа
		CORP c(species[s].g, stoch());

		float gposx = (float)(CORP::synth(c.gen_spe,15, 0))/(float)(0xffff);
		float gposy = (float)(CORP::synth(c.gen_spe,31,16))/(float)(0xffff);


		//произвольное расположение в пределах области
		switch(pattern)
		{
		//хаос
		case 0:
			c.x = lx1 + (lx2-lx1)*(0.1 + 0.8*rand()/RAND_MAX);
			c.y = ly1 + (ly2-ly1)*(0.1 + 0.8*rand()/RAND_MAX);
			break;
		//островки
		case 1:
			{
				float theta = 2*3.14*rndu();
				float r = rndu();
				c.x = lx1 + (lx2-lx1)*(0.2 + 0.7*gposx + 0.1*r*cos(theta));
				c.y = ly1 + (ly2-ly1)*(0.2 + 0.7*gposy + 0.1*r*sin(theta));
			}
			break;
		//сетка
		case 2:
			c.x = lx1 + (lx2-lx1)*( ((n*s+i)/storona)/(float)storona );
			c.y = ly1 + (ly2-ly1)*( ((n*s+i)%storona)/(float)storona );
			break;
		//сетка по секциям по видам
		case 3:
			c = CORP(species[ (int)((i/storona)/(float)storona * species.size())%species.size() ].g, stoch());
			c.x = lx1 + (lx2-lx1)*( (i/storona)/(float)storona );
			c.y = ly1 + (ly2-ly1)*( (i%storona)/(float)storona );
			break;
		}

		c.rx = c.x;
		c.ry = c.y;

		corp.push_back(c);
		massa += c.m;
	}

	sel = 0;
}

//=========================================================================================================
//добавить кучку одного вида
//=========================================================================================================
void OECOSYS::add (GENE spec, int n, float px, float py, float distr)
{
	//чтобы не выходило за рамку
	if(px < lx1*(1-distr)) px = lx1*(1-distr);
	if(px > lx2*(1-distr)) px = lx2*(1-distr);
	if(py < ly1*(1-distr)) py = ly1*(1-distr);
	if(py > ly2*(1-distr)) py = ly2*(1-distr);

	//добавить новый вид, если такого ещё нет
	bool est = false;
	for(int i=0; i<species.size(); i++) if(species[i].g == spec) est = true;
	if(!est) 
	{
		SPE_STAT ss;
		ss.g = spec;
		ss.m = 0;
		ss.qnt = 0;
		species.push_back(ss);
	}

	//забить память, если это вообще помогает
	corp.reserve(corp.size() + n);

	//добавить
	for(int i=0; i<n; i++)
	{
		//образец нового существа
		CORP c(spec, stoch());

		float theta = 2*3.14*rndu();
		float r = rndu();
		c.x = px + (lx2-lx1)*distr*r*cos(theta);
		c.y = py + (lx2-lx1)*distr*r*sin(theta);
		c.rx = c.x;
		c.ry = c.y;
		corp.push_back(c);
		massa += c.m;
	}
	sel = 0;
	calcul();
}



//=========================================================================================================
//родить
//=========================================================================================================
void OECOSYS::corp_gen (CORP& p1, CORP& p2)
{
	//рожать только из освобожденных ресурсов
	if( ultvid != 0)
	{
		p1.ngen++;
		p2.ngen++;
		CORP nov(p1, p2);
		CORP *ultimus = ultvid;
		ultvid = ultvid->vic;
		*ultimus = nov;
	}
	else
	{
		//corp.push_back(nov);
	}
}
//=========================================================================================================
//убить
//=========================================================================================================
void OECOSYS::corp_nec (CORP& cur)
{
	//включение текущего в список дырок
	cur.vic = ultvid;
	ultvid = &cur;

	//пометка как абсолютно неживого
	cur.est = false;
}

//=========================================================================================================
//выделить ближайший в пространстве
//=========================================================================================================
bool OECOSYS::selecta (float x, float y)
{
	auto prox = corp.begin();
	sel = &corp.front();
	CORP pseudomus(0,0);
	pseudomus.x = x;
	pseudomus.y = y;
	for(auto i = corp.begin(); i != corp.end(); i++ )
	{
			if(i->est && i->dist(pseudomus) < sel->dist(pseudomus)) 
			{
				sel = &(*i);
			}
	}
	return (sel == 0);
}


//=========================================================================================================
// вычислить динамику/намерения/планы для отдельно взятого чувака - можно параллелить
//=========================================================================================================
void OECOSYS::mod_a (CORP& cur)
{
	//совсем мертвых не считать
	if(cur.est && cur.vivus())
	{
		double accax = 0;	double accay = 0;	// намеренное ускорение по стимулу соседа
		double rax = 0;		double ray = 0;		// намеренное ускорение по стимулу соседа
		float minrax = 100;	float minray = 100;	// ускорение к ближайшему
		float iax = 0;		float iay = 0;		// произвольное скорение вне стимулов
		int nvic = 1;							// число и среднее расстояние до соседей

		//дистанция, с коротой текущий пожрёт чужого
		float crit_dist = genes[MAX_DIST_DEVOR].val(&cur);

		// дистанция с которой свои породят новых
		float copu_dist = genes[MAX_DIST_FUCK].val(&cur);

		//дальность обзора
		float act_dist = crit_dist +	genes[MAX_DIST_ACT].val(&cur);
		float vis_dist = act_dist + 	genes[MAX_DIST_VIS].val(&cur);
		float avgdist = vis_dist; 
		float mindist = vis_dist; 

		float sui_philia = genes[SUI_PHILIA].val(&cur);
		float sui_phobia = genes[SUI_PHOBIA].val(&cur);
		float opp_philia = genes[OPP_PHILIA].val(&cur);
		float opp_phobia = genes[OPP_PHOBIA].val(&cur);

		//количество отследиваемых в поле зрения
		int vis_qnt = genes[MAX_VIC_VIS].val(&cur);

		//масса начала репродукции
		float cur_adult_m = genes[MIN_REPRODUCT_MASS].val(&cur);
		bool cur_adult = cur.m > cur_adult_m;

		//повышение интереса к чужому если оный труп
		float necrophagia = 1.0 + 2*genes[NECROPHAGIA].val(&cur);

		//стремление к соседу своего вида, даже если он не достиг репродуктивной массы и спаривание невозможно
		float pedophilia = genes[PAEDOPHILIA].val(&cur);

		//----------------------------------------------------------------------------
		//поиск ближайших
		for(auto j=corp.begin(); j!=corp.end(); j++)
		{
			//исключить:
			if(	 j->est		 &&		// совсем мертвых
				 &(*j)!=&cur &&		// самого с собой
				 j->m>0 )			// только съеденных до нуля, но ещё не помеченных мертвыми
		 
			{
				//если данный сосед уже нашёл резон добавить текущего к себе
				if(j->vic == &cur)
					return;

				CORP& vic = *j;
				float dist = cur.dist(vic);

				//репродуктивная масса соседа
				float vic_adult_m = genes[MIN_REPRODUCT_MASS].val(&vic);

				float afactor = global_factor;

				//если этот сосед видим
				if(dist < vis_dist)
				{
					//компонент ускорения на этого соседа
					rax = 0; ray = 0;

					//расстояние и разности координат
					float dx = cur.x-vic.x;
					float dy = cur.y-vic.y;

					//свои - только живые нужны
					if(vic.gen_spe == cur.gen_spe)
					{
						//репродуктивен ли сосед
						bool vic_adult = (vic.m > vic_adult_m);

						//соприкосновение
						//если партнеры достаточно массивны для деторождения и не совпадают генами (нет инцесту!)
						if(dist<copu_dist && cur_adult && vic_adult && ((!incestus)?(cur.gen_ind != vic.gen_ind):true))
						{
							//добавить текущий в планы
							cur.vic = &vic;
							return;
						}
						//сближение или удаление
						else
						{
							
							//показатель зрелости обоих, >1 -> зрелы
							float a_ratio = (cur.m * vic.m ) / (cur_adult_m * vic_adult_m);
							afactor *= (1 - a_ratio) / (dist + 0.0001);
							if(a_ratio>1)
							{
								if(!vic_adult)	afactor *= pedophilia;
								else			afactor *= sui_philia;
							}
							else				afactor *= sui_phobia;

							//сближение (от зрелости) или удаление (по молодости)
							rax = afactor * dx;
							ray = afactor * dy;
						}
					}
					//чужие, в том числе умершие своей смертью
					else
					{
						//соприкосновение + съедание, если более меький чужак
						if(dist < crit_dist && cur.e > vic.e )
						{
							//добавить текущий в планы
							cur.vic = &vic;
							return;
						}
						//антагонист недалеко, главное исключить уже мёртвых
						else
						{
							//соотношение массы текущего и соседа - соотношение влечения и отвращения
							float m_ratio;

							
							#define AGGR_METHOD 2

							//---------------------------------------------------------------
							//аддитивный метод выяснения, нападать или бежать
							//ненормально большие скорости, слаженная реакция, тенденция к самоизоляции групп
							#if AGGR_METHOD == 0
							m_ratio = vic.m*opp_phobia - cur.m*opp_philia;
							if(vic.e<=0) m_ratio = -necrophagia*(1.0 + vic.m/3);
							afactor *= (m_ratio)*(cur_adult_m/cur.m) / (dist + 0.001);
							#endif
							//---------------------------------------------------------------

							//---------------------------------------------------------------
							//разграничивающий пропорциональный метод выяснения, нападать или бежать
							//начальная реакция всегда логична, личности влияют лишь на скорости
							//ограниченные диапазоны - индивидуальная реакция без коллективной истерии
							//риск застоя при выравнгивании плотности
							#if AGGR_METHOD == 1
							m_ratio = cur.m/vic.m;
							if(vic.e<=0) m_ratio = necrophagia*(1.0 + vic.m/3);
							afactor *= (1 - m_ratio)*(cur_adult_m/cur.m) / (dist + 0.001);
							if(m_ratio>1)	afactor *= opp_philia;
							else			afactor *= opp_phobia;
							#endif
							//---------------------------------------------------------------

							//---------------------------------------------------------------
							//резкий пропорциональный метод выяснения, нападать или бежать
							//слаженная реакция, малое число поеданий, тенденция к самоизоляции групп
							//благодаря большому диапазону скоростей события влекут более глобальное шевеление
							#if AGGR_METHOD == 2
							m_ratio = (0.1 + cur.m*opp_philia)/(0.1 + vic.m*opp_phobia);
							if(vic.e<=0) m_ratio = necrophagia*(1.0 + vic.m/3);
							afactor *= (1 - m_ratio)*(cur_adult_m/cur.m) / (dist + 0.001);
							#endif
							//---------------------------------------------------------------

							//сближение или удаление
							rax = afactor * dx;
							ray = afactor * dy;

						}
					}

					//если текущий сосед оказался ближе предыдущих, обновить звание ближайшего
					if(dist < mindist)	{ 	mindist = dist;	minrax = rax; minray = ray;	}
					nvic++;

					accax += rax;
					accay += ray;
				}

			}
		}

		//если до текущего расстояние совсем малое, остальные игнорируются
		if(mindist < act_dist)
		{
			accax = minrax;
			accay = minray;
		}
		else
		{
			accax /= nvic;
			accay /= nvic;
		}

		double mag = accax*accax + accay*accay;

		//дискомфорт от несоотвествия числа окружающих идеальному - тяга метаться
		float inquiet = ( 1 + abs(nvic-vis_qnt) ) / (nvic + vis_qnt);

		//праздношатание в произвольную сторону, зависит от целей в жизни
		double randfactor = 	(inquiet/(mag+0.1)) *cur.phaeno_uni(STOCH_MOT_INTENT)
								+ 10.0		*cur.phaeno_uni(STOCH_MOT_BASIS);

		randfactor *= global_factor;

		//малая энергия уменьшает ускорение
		float oustalosti = cur.e/cur.m;

		//результирующее намерение 
		cur.ax = ( accax + randfactor*rndb() ) * oustalosti;
		cur.ay = ( accay + randfactor*rndb() ) * oustalosti;


	}
}

//=========================================================================================================
// исполнить запланированные рождения и убийства - необходимо в одном потоке выполнять
//=========================================================================================================
void OECOSYS::mod_s (CORP& cur)
{
	if(cur.est && cur.vic!=0)
	{
		if(cur.vic->est) 
		{
			//процедура спаривания со стороны текущего
			if(cur.vic->gen_spe == cur.gen_spe)
			{
				float cur_adult = genes[MIN_REPRODUCT_MASS].val(&cur);
				float vic_adult = genes[MIN_REPRODUCT_MASS].val(cur.vic);
				if(cur.m > cur_adult && cur.vic->m > vic_adult)
					corp_gen(cur, *cur.vic);
			}
			//процедура поедания
			else
			{
				float crit_dist = genes[MAX_DIST_DEVOR].val(&cur);
				cur.devor(*cur.vic, crit_dist);
			}
		}
		cur.vic->vic = 0;
		cur.vic = 0;
	}
}

//=========================================================================================================
// вычислить кинематику интгерированием верле для отдельно взятого чувака - можно параллелить
//=========================================================================================================
void OECOSYS::mod_r (CORP& cur, double dT, double pdT)
{
	if(!cur.est)
	{	
		//убрать выделение
		if(sel == &cur) sel = 0;
		return;
	}

	double vx,vy;
	double bal = (dT + 1.0) / (pdT + 1.0);
	double bal2 = dT*(dT+pdT)/2;
	vx = (cur.x - cur.rx)*bal + cur.ax*bal2;
	vy = (cur.y - cur.ry)*bal + cur.ay*bal2;

	//квадрат скаляра скорости
	double magv = vx*vx + vy*vy;

	//поиск кандидатов на удаление (с отсосанной до нуля массой то есть съеденных)
	if(cur.e<=0)
	{
		if(magv < 0.01)
		{
			//пометить текущий как совсем мёртвый
			if(cur.m<=0) corp_nec(cur);

			//гарантировать отсутствие скорости
			cur.x = cur.rx;
			cur.y = cur.ry;

			//если просто массивный труп, исключить из просчёта
			return;
		}
	}
	//тикание жизни в секундах
	else cur.v += dt * 0.001;

	bool condmn = false;

	//отражение от границ
	if(cur.x + vx <= lx1) vx = -vx; else
	if(cur.y + vy <= ly1) vy = -vy;
	if(cur.x + vx >= lx2) vx = -vx; else
	if(cur.y + vy >= ly2) vy = -vy;


	//расход сил - если большое ускорение - отнимается энергия
	cur.e = cur.e / (0.99 + 0.1*magv);
	if(cur.e > cur.m)	cur.e = cur.m;

	//торможение при слишком высокой скорости
	//торможение от постоянной силы трения
	float fric = (1.0 - frictio*(1.0 + cur.m/5.0) ) * 10.0/(10.0 + magv);
	vx *= fric;
	vy *= fric;

	//обновление предыдущих
	cur.rx = cur.x;
	cur.ry = cur.y;

	//обновление актуальных
	cur.x += vx;
	cur.y += vy;

	//обнуление предыдуще вычисленных значений ускорения
	cur.ax = 0;  cur.ay = 0;

	//если включена смерть
	if(tempus_mortis)
	{
		//время умирать, но не удаляться
		if(cur.v > tempus_mortis*cur.limit()) 
		{
			cur.e = 0;
			cur.erase();
		}
	}
}


//=========================================================================================================
//для явной многопоточности - обработать конкретный лоскут из вектора
//=========================================================================================================
void OECOSYS::mod_ra(int a, int b)
{
	int n = b<corp.size()?b:corp.size();
	for(int i=a; i<n; i++)
	{
		mod_r(corp[i], std::min(dt,(double)max_dt), std::min(dt,(double)max_dt) );
		mod_a(corp[i]);
	}
}

//=========================================================================================================
//это не параллелится
//=========================================================================================================
void OECOSYS::mod_s()
{
	for(int i=0; i<corp.size(); i++)
	{
		mod_s(corp[i] );
	}
}

//=========================================================================================================
//полный шаг без разрезания на подмножества
//=========================================================================================================
void OECOSYS::iteratio(uint64_t nsec)
{
	//омп слишком тяжело для таких малеьнких кусков, выигрыша не дает
	#pragma omp parallel for
	for(int i=0; i<n(); i++)	{	mod_r (corp[i], std::min(dt,(double)max_dt), std::min(dt,(double)max_dt) );	mod_a (corp[i]);	}
	for(int i=0; i<n(); i++)	{	mod_s (corp[i]);		}
	synchro_post(nsec);
}

//=========================================================================================================
//подсчёт количеств
//=========================================================================================================
void OECOSYS::calcul()
{
	for(int j=0;j<species.size();j++)
	{
		species[j].qnt=0;
		species[j].m=0;
	}
	massa = 0;
	gener = 0;
	vivi = 0;
	for(auto i=corp.begin(); i!=corp.end(); i++)
	{
		if(i->est)
		{
			vivi++;
			if(i->e>0)
			{
				if(gener<i->gener) gener = i->gener;
				massa += i->m;
				for(int j=0;j<species.size();j++)
					if(i->gen_spe == species[j].g) 
					{
						species[j].qnt++;
						species[j].m += i->m;
					}
			}
		}
	}
}
