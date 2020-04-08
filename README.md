# NEAT
A C++ implementation of the Neuro-Evolution of Augmented Topologies

The goal is to create a simplified version of the NEAT algorithm with an easy-to-use interface. The namespace 'neat' is \
used as a portal to all the functionality and components needed to quickly use the algorithm while hiding all the \
under-the-hood implementations.

For more information on the NEAT algorithm...
  1. The original paper: http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf
  2. The inventor's maintenance page: https://www.cs.ucf.edu/~kstanley/neat.html
  3. Original software release: http://nn.cs.utexas.edu/?neat-c
  4. Video of someone else's implementation: https://www.youtube.com/watch?v=qv6UVOQ0F44

Key Differences
  1. If a gene becomes frozen because of a new node innovation, it will never again be unfrozen.
  2. Separated out the concept of innovation from gene. Innovation numbers aren't used for breeding anymore. That is now \
        the function of the gene id. 

Assumptions
  1. Innovations of all types do not need to be generational.
  2. During breeding, if you take the stronger genome's disjoint/excess genes, you will not get any disconnected nodes \
        in the final genome produced. This is an important assumption due to making the innovations generation independent.

Simplifications
  1. Traits are out! Not sure what the original intentions were and as far as I could tell, they were not being used.
  2. Innovations are not generational. If a mutation causes a connection between nodes 4 and 5, it shouldn't matter \
        if it happened during generation 1 or generation 100. It's the same gene.
  3. Initial connections guarantee each input and output node contains at least one connection. Other than that, each \
        initial genome is randomly connected.

To do list
  1. Implement all mutation types.
  2. Implement all breeding types.
  3. Implement networks.
  4. Pass for const correctness.
  5. Extract activation functions to their own class.
  6. Implement logging.
  7. Should a Genome be friends with the Mutators?
  8. It would be super duper cool to have a history of everything that happened throughout evolution. This should be attainable \
        since none of the information is destroyed until reset() is called. It could even include pointers to the previous generations.
    a. Create a genome history invariant based on whether it was bred or mutated from a previous generation.
    b. Create a species history that tracks age and the master genome of each generation.