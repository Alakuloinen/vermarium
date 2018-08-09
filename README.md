# vermarium
A simple visual biology/genetics/ecosystems model.

## Model Concept

### Mechanics

1. There are N creatures moving in a square-limited floating-point 2D space.
2. Every creature has stable mass and related variable stamina parameter. Zero stamina means a cadaver which doesn't move.
3. Mass determines stamina range, stamina limits acceleration, big mass allows higher accelerations but affects friction and reduces velocity.
4. Mass is constant while moving but changes during sex and violence acts.
5. Reaching a defined short distance between two creatures can trigger them mating or devouring.
  * While devouring a creature with higher stamina kills the rival and acquires a part of its mass. If the victim's mass turns zero, it completely disappears, otherwise it remains lying as a dead meat. So the easiest victim is such a cadaver (stamina=0), a result of previous killing or a natural death.
  * While mating a new creature is instantly born, acquiring a part of mass of both parents (leaving them alive underweighted), so such an act is possible if both parents gain mass twice as big as minimal mass of a newborn. 
  As the children remain within critical distance and can be still massive enough, the process could look like a burst, producing dozens of weak babies.
  To prevent this a virginity age is introduced protecting newborns from "pregnancy" for some time. Anyway instead of a burst you get a fountain.
1. In other cases a body tracks neighbors within its individual field of view and acts in some reasonable way, e.g. looking for sex and avoiding predators.
  * There is a one goal distance, a creature having a neighbors within it ignores the others and aims at the closest among them. 
1. Creatures cannot see stamina, only mass, so dwarfs would avoid giants, but a giant exhausted by a mighty acceleration can accidentally get killed by a standing still dwarf.
1. A creature can be mortal (this can be switched off) so reaching a defined (partly random) age it instantly becomes dead and can be used as a free food.

### Genetics

1. Every creature belongs to a species. The set of species is explicitly determined when creating the ecosystem.
1. Every creature has genes that determine various parameters of its life, such as reproducting mass, view distance, acceleration towards prey etc.
1. Genes divided into species-related and individual so that the phenotype is a linear combination of both with adjustable factors.
1. Only creatures of the same species can copulate and give birth to a new creature. If incest is switched off creatures can't have children if their individual genes are exactly the same.
1. Any other species are considered enemies and trigger avoiding more massive neighbors and hunting those less massive.
1. When killed or naturally dead a creature loses its genes and becomes an alien tasty meat for anybody.
1. A newborn inherits both parents' individual genes in some adjustable way, by default using crossingover, i.e. every gene is randomly taken from ether parent1 or parent2.
1. With a certain probability a mutation occurs causing a parent gene be slightly changed before creature installed into the child's genome.

Due to a low range of model parameters + lack of author's knowledge some true genetic models were abandonned or simply don't work correctly.
So the goal of the project evolved into reaching an addictive visual drama instead of pure investigation.
There are no sophisticaed models delimiting possibility of hybridisation between two random creatures, no selfish genes gaining proper complexes for themselves, anyway it's hardly demonstrated in colored real-time pixels.
The main focus of the program is thus showing a competition between differently skilled species in a form of an epic worm battle. 
Still there is a possibility to tune the factor individual genes affect the phenotype yielding fuzzy species where a true evolution
of individuals occurs, but this mode is less spectacular and more unstable as the range of possibilities is much lower than the range of real objects.

Recent updates introduce a new feature, a species mutation probability. Making it non zero causes some children be born with slightly different species genes.
Such mutants can easily eat up all their siblings as well as parents, but they are usually alone, unable to mate with anybody.
It doesn't mean they are doomed and useless.
The genes are discrete, any casual mutation is indeed an increment or decrement of the gene, so the formation of two identical mutants is rather possible.
Leaving the simulation for an hour you risk to find none of the initial species, but some unknown forms of life.


## Implementation

The main model is writen in pure C++ with pure STL as a typical N body algorithm with time-adjusted Verlet integrations. For the sake of multithreading a continuous vector is used, explicitly divided into strips. For the killed a flag 'dead' is used, the newborn is regenerated from the dead without increasing the vector size and rearranging the threads (currently). This fundamental disbalance does not play a significant role because the vector is initialized by minors which need much meat to grow up to reproductive mass.

The values of the genes are generated randomly except the manual scattering mode in which an exact species gene is input by user in form of a number. This mode also allows user to put a cluster of creatures onto defined part of the field. Anyway, noticing an interesting behaviour the user can pause and resume simulation, restore the initial state and live through it again or export the ecosystem's current state to a file. 

The GUI is written using Qt 5+ including Qt OpenGL widget. Beings are represented as colored dots of a size corresponding to their mass and color corresponding to their species genes. The coloring mode can be changed to represend stamina, age, or generation.

The user can select any creature by mouse clicking close to it and observe its individual phenotype parameters as well as its species genotype in form of a number which actually says nothing but can be saved and reused.

Calculations are accelerated by a custom and hardly optimal QThread-based thread manager, still making a significant increase in speed comparing to asingle-threaded version. There is also an OpenMP version of the routine but it's either not optimized or simply useless in such a short timesteps since the only thing it speeds up is the CPU cooler.
