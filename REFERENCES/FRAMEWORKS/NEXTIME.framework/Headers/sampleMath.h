
/*
 * Macros used for performing operations on doubles used to represent time.
 * These functions pay particular attention to errors which can accumulate due
 * to the approximate nature of floating point representations.
 */
 
/*
 * One, two, and three bits of error in relation to a 48 bit significand IEEE
 * representation of the value 1.0.
 */
#define ONE_ULPS	.000000000000003552713678800500929355621337890625
#define TWO_ULPS	.000000000000010658141036401502788066864013671875
#define THREE_ULPS	.000000000000024868995751603506505489349365234375
#define FOUR_ULPS	.000000000000053290705182007513940334320068359375

/*
 * When performing many operations, we tend to lose precision, which shows up
 * as truncation towards zero.  We must compensate for this prior to quantizing
 * a double into an integer, to avoid 'off by 1' errors.
 */

#define SAMPLE_INDEX( dT, duration )	((int)(((dT)/(duration)) + 0.5))

/*
 * Default tolerance, or error permitted when comparing sample times for
 * equivalence.  This value is a maximum, and media objects may adjust it
 * downward so as to represent no more than (minimum sample duration / 2).
 */
#define DEFAULT_TOLERANCE	(1.0/1200.0) /* half of QuickTime's 1/600 */
					     /* second default resolution */

/*
 * Fuzzy value comparison function.  Used in testing sample times for
 * equivalence, where the tolerance represents half the minimum non-zero
 * sample duration. 
 */
 static inline BOOL
isEquivalent( double t1, double t2, double tolerance )
{
	if (	t1 == t2
	    ||	((t1 + tolerance) >= t2 && ((t1 - tolerance) < t2 )) )
	    	return YES;
		
	return NO;
}

