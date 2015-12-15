Probabilistic Scheduler for commodity Hardware Transactional Memories
============

*How to compile*

To compile the following alternatives, choose the correct macros to be defined:

*Seer*
 - USE_SEER should be enabled to enable the following ones:
 - USE_TX_LOCKS: use the Transaction Locks to avoid conflict aborts
 - USE_CPU_LOCKS: use the Core Locks to avoid capacity aborts
 - USE_HTM_LOCKS: use HTM tx to acquire the transaction locks
 - USE_GRADIENT_DESCENT: use Gradient Descent to compute the thresholds

*HLE*
 - USE_HLE 

*SCM*
 - USE_SCM

*RTM*
 - (define nothing, default)


Examples:
 - Compiling Seer with everything enabled for intruder with 8 threads and 5 retries: bash build.sh 5 1 8 3 intruder "-DUSE_SEER -DUSE_TX_LOCKS -DUSE_CPU_LOCKS -DUSE_HTM_LOCKS -DUSE_GRADIENT_DESCENT"
 - Compiling RTM for genome with 7 threads and 5 retries: bash build.sh 5 1 7 5 genome ""
 - Compiling SCM for vacation with 2 threads and 5 retries: bash build.sh 5 1 2 3 vacation "-DUSE_SCM"


Note that the scripts automatically identify the processor (Intel or IBM) to compile the correct HTM directives. It also tries to identify the machine to reserve the correct number of core locks, but this should be tuned for new machines.


For questions, contact the author: Nuno Diegues - nmld@tecnico.ulisboa.pt

When using this work, please cite accordingly: Nuno Diegues, Paolo Romano and Stoyan Garbatov, "Seer: Probabilistic Scheduling for Hardware Transactional Memory", Proceedings of the Symposium on Parallel Algorithms and Architectures, SPAA 2015

You may also find the following papers relevant for citation: 

Nuno Diegues, Paolo Romano, and Luis Rodrigues, "Virtues and Limitations of Commodity Hardware Transactional Memory", Proceedings of the International Conference on Parallel Architectures and Compiler Techniques, PACT 2014

and 

Nuno Diegues and Paolo Romano, "Self-Tuning Intel Transactional Synchronization Extensions", Proceedings of the International Conference on Autonomic Computing, ICAC 2014

This work was supported by national funds through Fundação para a Ciência e Tecnologia (FCT) with reference UID/CEC/50021/2013 and by the GreenTM project (EXPL/EEI-ESS/0361/2013).
