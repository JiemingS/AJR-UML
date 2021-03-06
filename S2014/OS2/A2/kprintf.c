/* kprintf.c - kprintf, kputc, savestate, rststate */

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <slu.h>
#include <tty.h>


LOCAL	int	savedev, savecrstat, savectstat;
LOCAL	char	saveps;
LOCAL   kputc();
LOCAL   savestate();
LOCAL   rststate();



/*------------------------------------------------------------------------
 *  kprintf  --  kernel printf: formatted, unbuffered output to CONSOLE
 *------------------------------------------------------------------------
 */
int kprintf(char *fmt, int args)     /* Derived by Bob Brown, Purdue U.	*/
{
        int     kputc();

        savestate(CONSOLE);
        _doprnt(fmt, &args, kputc, CONSOLE);
        rststate();
        return(OK);
}

#define DELAY	100
/*------------------------------------------------------------------------
 *  kputc  --  write a character on the console using polled I/O
 *------------------------------------------------------------------------
 */
LOCAL	kputc(int device, 
	      register char c)  /* character to print from _doprnt      */
{
	struct	csr	*csrptr;
	struct	tty	*ttyptr;
	int	slowdown;	/* added to delay polling, because	*/
				/*   polling immediately after a	*/
				/*   transmit seems to cause trouble	*/
	if ( c == 0 )
		return;
	if ( c == NEWLINE )
		kputc( device, RETURN );
	csrptr = (struct csr *)devtab[device].dvcsr;	/* dev.	address	*/
	ttyptr = (struct tty *)devtab[device].dvioblk;	/* control block*/

	if (ttyptr && (ttyptr->oheld || (ttyptr->oflow&&/* flow control	*/
		(csrptr->crstat & SLUREADY) &&
		(csrptr->crbuf & SLUCHMASK) == ttyptr->ostop))) {
		do {
		    while (!(csrptr->crstat&SLUREADY)) ;/* wait for char*/
		} while ((csrptr->crbuf&SLUCHMASK) == ttyptr->ostop);
		ttyptr->oheld = FALSE;
	}

	while (!(csrptr->ctstat & SLUREADY)) ;		/* poll for idle*/
	csrptr->ctbuf = c;				/* transmit char*/
	for (slowdown=0;slowdown<DELAY;slowdown++) ;	/* wait a bit	*/
	while (!(csrptr->ctstat & SLUREADY)) ;		/* poll for idle*/
	return;
}

/*------------------------------------------------------------------------
 *  savestate  --  save the console control and status register
 *------------------------------------------------------------------------
 */
LOCAL	savestate(int device)
{
    sigset_t ps;
	disable(ps);
	saveps = ps;
	savedev = device;
	savecrstat = ((struct csr *)devtab[device].dvcsr)->crstat
		& SLUENABLE;
	((struct csr *)devtab[device].dvcsr)->crstat = SLUDISABLE;
	savectstat = ((struct csr *)devtab[device].dvcsr)->ctstat
		& SLUENABLE;
	((struct csr *)devtab[device].dvcsr)->ctstat = SLUDISABLE;
	return;
}

/*------------------------------------------------------------------------
 *  rststate  --  restore the console output control and status register
 *------------------------------------------------------------------------
 */
LOCAL	rststate()
{
	sigset_t ps;

	((struct csr *)devtab[savedev].dvcsr)->crstat = savecrstat;
	((struct csr *)devtab[savedev].dvcsr)->ctstat = savectstat;
	ps = saveps;
	restore(ps);
	return;
}
