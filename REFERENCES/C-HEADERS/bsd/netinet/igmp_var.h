/*
 * Internet Group Management Protocol (IGMP),
 * implementation-specific definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 1.1
 */

struct igmpstat {
	u_int	igps_rcv_total;			/* total IGMP messages received    */
	u_int	igps_rcv_tooshort;		/* received with too few bytes     */
	u_int	igps_rcv_badsum;		/* received with bad checksum      */
	u_int	igps_rcv_queries;		/* received membership queries     */
	u_int	igps_rcv_badqueries;	/* received invalid queries        */
	u_int	igps_rcv_reports;		/* received membership reports     */
	u_int	igps_rcv_badreports;	/* received invalid reports        */
	u_int	igps_rcv_ourreports;	/* received reports for our groups */
	u_int	igps_snd_reports;		/* sent membership reports         */
};


