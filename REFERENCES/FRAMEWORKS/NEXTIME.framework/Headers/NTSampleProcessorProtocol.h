/*
 *  NTSampleProcessorProtocol.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	A set of protocols defining expected API in components used to
 *	manipulate samples.
 *
 *	13 Jan 1994 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSArray.h>
#import "NTSampleBuffer.h"

/*
 * NTConfiguration protocol: specifies how a sample processor
 * is to be configured, and how it reports it's configuration and
 * capabilities.
 *
 * Configuration for Sample Processors:
 *
 *
 * Each sample processor works on samples of a given media type (i.e. Audio
 * or Video).  Within each media type, there sample format types 
 * (i.e. Compressed, or Raw) and format subtypes. (i.e. Cinepak
 * Compressed, etc.).  A Sample processor typically contains an input
 * port and an output port, each of which can be configured with a sample
 * format type and subtype.  The format type and subtypes supported by
 * a component are assumed to static properties. A complete format 
 * description is embodied in a sampleConfiguration dictionary.  
 * This contains the format type and subtype as well as any other information 
 * needed to concretely specify the format.
 *
 * When processing components are connected to each other, a format negotiation
 * takes place.  A processor configuration is set via the setConfiguration:
 * message.  Configuration is continued until the components in question
 * can handle the configuration request.
 *
 *
 * Configuration process:
 *
 * After being created using alloc/init, the sample processor object is
 * sent a setEnvironment: message.  The environment dictionary describes the
 * current session and configuration goals.
 *
 * The dictionary passed into setConfiguration: typically has two keys:
 * NTSampleInput, and NTSampleOutput.  The value of these keys are sub    
 * dictionaries containing the desired input and output goals.  The component
 * should examine these dictionaries and make any changes it wants in place.
 * The configuration logic will note the changes and present them in turn to
 * any other affected components.  The logic then continues bidding the 
 * configuration until either convergence is reached, or a format cannot be
 * agreed on.  If an agreement cannot be reached the configuration logic will
 * try to use a format adaptor to make up the difference.
 *
 * Once a configuration is complete, each element of the configuration is
 * sent a finalizeConfiguration message.  If this returns NO, the
 * configuration is not considered viable, and is rejected.
 *
 * 
 */

@protocol NTConfiguration <NSObject>
- (void) setEnvironment:(bycopy NSDictionary *)environment;
- (bycopy NSDictionary *) setConfiguration:
		(bycopy NSDictionary *) config;
- (bycopy NSDictionary *) configuration;
- (BOOL) setOutputObject: obj;
- (BOOL) finalizeConfiguration;
- (bycopy NSDictionary *) measureConfiguration:
		(bycopy NSDictionary *) query;
@end

/*
 * NTSampleProcessor protocol: specifies API by which samples are passed
 * to a sample processor.
 *
 * The NTSampleProcessor may also be capable of providing a NTMutableSample
 * buffer into which a previous NTSampleProcessor can deposit it's samples.
 * This may be used to optimize output paths by letting the previous
 * NTSampleProcessor deposit processed samples into dedicated hardware,
 * such as a frame buffer or audio DMA buffer.
 *
 * If an NTSampleProcessor cannot vend a NTMutableSample buffer,
 * it should still implement the inputBufferForPort: method,
 * returning a value of nil.
 *
 * Graphics NTSampleProcessor which return an input buffer must guarantee that
 * the buffer contains the accumulated contents of previous buffers passed to
 * the object through writeSample:toPort:.  This is required to support
 * compressors implementing temporal compression.
 * 
 * Objects which can return an output buffer must still support 
 * writeSample:toPort: of NTSample objects which do not originate
 * from the inputBufferForPort: method.
 *
 * An NTSampleProcessor which obtains a NTMutableSample object from another
 * NTSampleProcessor is required to pass that NTMutableSample object back
 * to the other NTSampleProcessor on it's next call to writeSample:toPort:.
 *
 * Output devices should implement the NTSampleProcessor protocol.
 * The protocol does not fully define the API for an output device,
 * however.  The output devices may also implement higher performance'
 * API tuned for the specific data being handled.
 */

/*
 * NTSampleConsumer.  The actually writing methods are separated out here
 * since some objects can implement these and be wired up into sample  
 * processing pipelines (via setOutputObject:).  For example NTSampleFIFO
 * and NTMedia implement this protocol.
 */

@protocol NTSampleConsumer <NSObject>
- (id <NTMutableSampleBuffer>)inputBuffer;
- (void)writeSample: (id <NTSampleBuffer>) sample; 
@end

@protocol NTSampleProcessor <NTConfiguration, NTSampleConsumer>

/*
 * pause allows asynchronous devices to enqueue samples without
 * actualization. (aka pre-roll)  When a processor is paused, it is
 * in an enabled state, but is incapable of passing samples to it's outlet.
 * -run places the sample processor in an enabled state, with the ability
 * to pass samples to it's outlet.
 *
 * For example, in prerolling a movie, the output processor in a chain might
 * be paused.  Samples would then be passed into the processing chain until
 * [outputDevice samplesEnqueued] returns YES. 
 */
- (void)run;
- (void)stop;
- (BOOL)isStopped;	 /* YES if passing samples to outlet is inhibited */
- (BOOL)samplesEnqueued; /* YES if samples are enqueued */

/*
 * flushSamples: waits for any enqueued samples to be completely processed,
 * if abortFlag is true, enqueued samples need not be rendered and
 * can be tossed. In any event, after this method is called, there
 * is no pending data in the sample processor.
 */
- (void)flushSamples:(BOOL)abortFlag; 
@end

/*
 * An NTSamplePipeline implements the NTSampleProcessor protocol, 
 * and contains a series of components used to implement the configured
 * sample processing operation.  It's API also includes a method which returns
 * the ordered list of processing component objects.  Each of these objects
 * in turn implements the NTSampleProcessor protocol.  The list is ordered with
 * the input processor first, and the sample sink, or output stage last.
 *
 * The list is owned by the NTSamplePipeline and should not be freed.
 */
@protocol NTSamplePipeline <NTSampleProcessor>
- (NSArray *)nodeList;
@end

/*
 * NTSampleGenerator protocol: specifies API for an asynchronous sample source.
 * The source will have it's sample target specified by means of the
 * NTConfiguration protocol.
 *
 * Input devices should implement the NTSampleGenerator
 * protocol.  The protocol does not fully define the API for a sample
 * source, however.  The source devices may also implement higher
 * performance API tuned for the specific data being handled.
 *
 * The -run and -pause methods do not imply anything with respect to sample
 * ordering or timing.  They exist simply as a means of stopping or starting
 * the flow of samples.  Temporal semantics and implications are outside the
 * scope of this protocol.
 */
@protocol NTSampleGenerator <NTConfiguration>
- (void)run;
- (void)stop;
- (BOOL)isStopped;
@end

/*
 * NTSampleFilter protocol:  This protocol is implemented by all objects
 * which accept and transform samples into a new form.  Objects in this
 * group include software compressors and decompressors.  The object performs
 * it's encoding or decoding operation on 'sample', frees 'sample', and returns
 * the new encoded or decoded sample.
 *
 * The implementor needs to be able to process samples `out-of-context'
 * (i.e. without seeing neighboring samples in the sequence.).
 * This is most often used in raw format converters but can also be used
 * to compress or decompress `sync' samples in encoded form.
 * The NEXTIME implementation guarantees that the sample filter will never be
 * passed unordered non-sync samples. 
 */
@protocol NTSampleFilter <NTSampleProcessor>
- (id <NTSampleBuffer>)processSampleFrom:(id <NTSampleBuffer>)sample;
@end


