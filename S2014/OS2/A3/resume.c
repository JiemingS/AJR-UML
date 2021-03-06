/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	sigset_t ps;			/* saved processor status	*/
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
    pptr = &proctab[pid];
//    if (isbadpid(pid) || (pptr = &proctab[pid])->pstate != PRSUSP) {
    if ((isbadpid(pid)) || (pptr->pstate != PRSUSP)) {
        restore(ps);
        return(SYSERR);
    }
    prio = pptr->pprio;
    ready(pid, RESCHYES);
    restore(ps);
    return(prio);
}
