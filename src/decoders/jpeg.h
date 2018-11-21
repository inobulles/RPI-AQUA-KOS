
#ifndef __AQUA__DECODERS_JPEG_H
	#define __AQUA__DECODERS_JPEG_H
	
	#include "root.aqua"
	#include "surf.aqua"
	
	#include <stdio.h>
	#include <assert.h>
	
	#define OMXJPEG_OK 0
	#define OMXJPEG_ERROR_ILCLIENT_INIT -1024
	#define OMXJPEG_ERROR_OMX_INIT -1025
	#define OMXJPEG_ERROR_MEMORY -1026
	#define OMXJPEG_ERROR_CREATING_COMP -1027
	#define OMXJPEG_ERROR_WRONG_NO_PORTS -1028
	#define OMXJPEG_ERROR_EXECUTING -1029
	#define OMXJPEG_ERROR_NOSETTINGS -1030
	
	typedef struct _OPENMAX_JPEG_DECODER OPENMAX_JPEG_DECODER;
	
	int setupOpenMaxJpegDecoder(OPENMAX_JPEG_DECODER** decoder);
	int decodeImage(OPENMAX_JPEG_DECODER* decoder, char* sourceImage, size_t imageSize);
	
	void cleanup(OPENMAX_JPEG_DECODER* decoder);
	
	#define TIMEOUT_MS 2000
	
	typedef struct _COMPONENT_DETAILS {
		COMPONENT_T* component;
		OMX_HANDLETYPE handle;
		
		int in_port;
		int out_port;
		
	} COMPONENT_DETAILS;

	struct _OPENMAX_JPEG_DECODER {
		ILCLIENT_T* client;
		
		COMPONENT_DETAILS* image_decoder;
		COMPONENT_DETAILS* image_resizer;
		
		OMX_BUFFERHEADERTYPE** pp_input_buffer_header;
		int input_buffer_header_count;
		OMX_BUFFERHEADERTYPE* p_output_buffer_header;
		
	};

	static int buffer_index = 0;

	int port_settings_changed(OPENMAX_JPEG_DECODER* decoder) {
		OMX_PARAM_PORTDEFINITIONTYPE port_definition;
		
		port_definition.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
		port_definition.nVersion.nVersion = OMX_VERSION;
		port_definition.nPortIndex = decoder->image_decoder->out_port;
		OMX_GetParameter(decoder->image_decoder->handle, OMX_IndexParamPortDefinition, &port_definition);

		unsigned int width = (unsigned int) port_definition.format.image.nFrameWidth;
		unsigned int height = (unsigned int) port_definition.format.image.nFrameHeight;
		
		port_definition.nPortIndex = decoder->image_resizer->in_port;
		OMX_SetParameter(decoder->image_resizer->handle, OMX_IndexParamPortDefinition, &port_definition);
		
		OMX_SetupTunnel(decoder->image_decoder->handle, decoder->image_decoder->out_port, decoder->image_resizer->handle, decoder->image_resizer->in_port);

		OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandPortEnable, decoder->image_decoder->out_port, NULL);
		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandPortEnable, decoder->image_resizer->in_port, NULL);
		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandStateSet, 1, OMX_StateIdle, 1, 0, TIMEOUT_MS);
		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandPortEnable, 1, decoder->image_decoder->out_port, 1, 0, TIMEOUT_MS);
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandPortEnable, 1, decoder->image_resizer->in_port, 1, 0, TIMEOUT_MS);
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventPortSettingsChanged, decoder->image_resizer->out_port, 1, 0, 1, 0, TIMEOUT_MS);

		ilclient_disable_port(decoder->image_resizer->component, decoder->image_resizer->out_port);

		port_definition.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
		port_definition.nVersion.nVersion = OMX_VERSION;
		port_definition.nPortIndex = decoder->image_resizer->out_port;
		
		OMX_GetParameter(decoder->image_resizer->handle, OMX_IndexParamPortDefinition, &port_definition);

		port_definition.format.image.eCompressionFormat = OMX_IMAGE_CodingUnused;
		port_definition.format.image.eColorFormat = OMX_COLOR_Format32bitABGR8888;
		port_definition.format.image.nFrameWidth = width;
		port_definition.format.image.nFrameHeight = height;
		port_definition.format.image.nStride = 0;
		port_definition.format.image.nSliceHeight = 0;
		port_definition.format.image.bFlagErrorConcealment = OMX_FALSE;

		OMX_SetParameter(decoder->image_resizer->handle, OMX_IndexParamPortDefinition, &port_definition);
		OMX_GetParameter(decoder->image_resizer->handle, OMX_IndexParamPortDefinition, &port_definition);

		ilclient_change_component_state(decoder->image_resizer->component, OMX_StateExecuting);

		printf("JPEG width = %d, height = %d, output colour format = 0x%x, buffer size = %d\n", port_definition.format.image.nFrameWidth, port_definition.format.image.nFrameHeight, port_definition.format.image.eColorFormat, port_definition.nBufferSize);

		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandPortEnable, decoder->image_resizer->out_port, NULL);

		int error_code = OMX_AllocateBuffer(decoder->image_resizer->handle, &decoder->p_output_buffer_header, decoder->image_resizer->out_port, NULL, port_definition.nBufferSize);
		
		if (error_code != OMX_ErrorNone) {
			perror("Eror allocating buffer");
			fprintf(stderr, "OMX_AllocateBuffer returned 0x%x allocating buffer size 0x%x\n", error_code, port_definition.nBufferSize);
			
			return OMXJPEG_ERROR_MEMORY;
			
		}
		
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandPortEnable, 1, decoder->image_resizer->out_port, 1, 0, TIMEOUT_MS);
		return OMXJPEG_OK;
		
	}
	
	int port_settings_changed_again(OPENMAX_JPEG_DECODER* decoder) {
		ilclient_disable_port(decoder->image_decoder->component, decoder->image_decoder->out_port);
		ilclient_disable_port(decoder->image_resizer->component, decoder->image_resizer->in_port);

		OMX_PARAM_PORTDEFINITIONTYPE port_definition;

		port_definition.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
		port_definition.nVersion.nVersion = OMX_VERSION;
		port_definition.nPortIndex = decoder->image_decoder->out_port;

		OMX_GetParameter(decoder->image_decoder->handle, OMX_IndexParamPortDefinition, &port_definition);

		port_definition.nPortIndex = decoder->image_resizer->in_port;
		OMX_SetParameter(decoder->image_resizer->handle, OMX_IndexParamPortDefinition, &port_definition);

		ilclient_enable_port(decoder->image_decoder->component, decoder->image_decoder->out_port);
		ilclient_enable_port(decoder->image_resizer->component, decoder->image_resizer->in_port);

		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventPortSettingsChanged, decoder->image_resizer->out_port, 1, 0, 0, 0, TIMEOUT_MS);

		return OMXJPEG_OK;
		
	}

	int prepare_resizer(OPENMAX_JPEG_DECODER* decoder) {
		decoder->image_resizer = malloc(sizeof(COMPONENT_DETAILS));
		
		if (decoder->image_resizer == NULL) {
			perror("malloc image resizer");
			return OMXJPEG_ERROR_MEMORY;
			
		}
		
		int error_code = ilclient_create_component(decoder->client, &decoder->image_resizer->component, "resize", ILCLIENT_DISABLE_ALL_PORTS | ILCLIENT_ENABLE_INPUT_BUFFERS | ILCLIENT_ENABLE_OUTPUT_BUFFERS);
		
		if (error_code != 0) {
			perror("image resizer");
			return OMXJPEG_ERROR_CREATING_COMP;
			
		}
		
		decoder->image_resizer->handle = ILC_GET_HANDLE(decoder->image_resizer->component);
		OMX_PORT_PARAM_TYPE port;
		
		port.nSize = sizeof(OMX_PORT_PARAM_TYPE);
		port.nVersion.nVersion = OMX_VERSION;

		OMX_GetParameter(ILC_GET_HANDLE(decoder->image_resizer->component), OMX_IndexParamImageInit, &port);
		
		if (port.nPorts != 2) {
			return OMXJPEG_ERROR_WRONG_NO_PORTS;
			
		}
		
		decoder->image_resizer->in_port = port.nStartPortNumber;
		decoder->image_resizer->out_port = port.nStartPortNumber + 1;
		decoder->p_output_buffer_header = NULL;

		return OMXJPEG_OK;
		
	}

	int prepare_image_decoder(OPENMAX_JPEG_DECODER* decoder) {
		decoder->image_decoder = malloc(sizeof(COMPONENT_DETAILS));
		
		if (decoder->image_decoder == NULL) {
			perror("malloc image decoder");
			return OMXJPEG_ERROR_MEMORY;
			
		}

		int error_code = ilclient_create_component(decoder->client, &decoder->image_decoder->component, "image_decode", ILCLIENT_DISABLE_ALL_PORTS | ILCLIENT_ENABLE_INPUT_BUFFERS);

		if (error_code != 0) {
			perror("image decode");
			return OMXJPEG_ERROR_CREATING_COMP;
			
		}
		
		decoder->image_decoder->handle = ILC_GET_HANDLE(decoder->image_decoder->component);
		OMX_PORT_PARAM_TYPE port;
		
		port.nSize = sizeof(OMX_PORT_PARAM_TYPE);
		port.nVersion.nVersion = OMX_VERSION;

		OMX_GetParameter(decoder->image_decoder->handle, OMX_IndexParamImageInit, &port);
		
		if (port.nPorts != 2) {
			return OMXJPEG_ERROR_WRONG_NO_PORTS;
			
		}
		
		decoder->image_decoder->in_port = port.nStartPortNumber;
		decoder->image_decoder->out_port = port.nStartPortNumber + 1;

		return OMXJPEG_OK;
		
	}

	int startup_image_decoder(OPENMAX_JPEG_DECODER* decoder) {
		ilclient_change_component_state(decoder->image_decoder->component, OMX_StateIdle);
		OMX_IMAGE_PARAM_PORTFORMATTYPE image_port_format;
		
		memset(&image_port_format, 0, sizeof(OMX_IMAGE_PARAM_PORTFORMATTYPE));
		
		image_port_format.nSize = sizeof(OMX_IMAGE_PARAM_PORTFORMATTYPE);
		image_port_format.nVersion.nVersion = OMX_VERSION;
		image_port_format.nPortIndex = decoder->image_decoder->in_port;
		image_port_format.eCompressionFormat = OMX_IMAGE_CodingJPEG;
		
		OMX_SetParameter(decoder->image_decoder->handle, OMX_IndexParamImagePortFormat, &imagePortFormat);
		OMX_PARAM_PORTDEFINITIONTYPE port_definition;
		
		port_definition.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
		port_definition.nVersion.nVersion = OMX_VERSION;
		port_definition.nPortIndex = decoder->image_decoder->in_port;
		
		OMX_GetParameter(decoder->image_decoder->handle, OMX_IndexParamPortDefinition, &port_definition);
		OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandPortEnable, decoder->image_decoder->in_port, NULL);
		
		decoder->inputBufferHeaderCount = port_definition.nBufferCountActual;
		decoder->pp_input_buffer_header = (OMX_BUFFERHEADERTYPE**) malloc(sizeof(void) * decoder->inputBufferHeaderCount);
		
		int i;
		for (i = 0; i < decoder->inputBufferHeaderCount; i++) {
			if (OMX_AllocateBuffer(decoder->image_decoder->handle, &decoder->pp_input_buffer_header[i], decoder->image_decoder->in_port, (void*) i, port_definition.nBufferSize) != OMX_ErrorNone) {
				perror("Allocate decode buffer");
				return OMXJPEG_ERROR_MEMORY;
				
			}
			
		}
		
		int error_code = ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandPortEnable, 0, decoder->image_decoder->in_port, 0, 0, TIMEOUT_MS);
		
		if (error_code != 0) {
			fprintf(stderr, "Did not get port enable %d\n", ret);
			return OMXJPEG_ERROR_EXECUTING;
			
		}
		
		error_code = OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
		
		if (error_code != 0) {
			fprintf(stderr, "Error starting image decoder %x\n", ret);
			return OMXJPEG_ERROR_EXECUTING;
			
		}
		
		error_code = ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_StateExecuting, 0, 0, 1, 0, TIMEOUT_MS);
		
		if (error_code != 0) {
			fprintf(stderr, "Did not receive executing stat %d\n", error_code);
			//~ return OMXJPEG_ERROR_EXECUTING;
			
		}

		return OMXJPEG_OK;
		
	}

	int setup_open_max_jpeg_decoder(OPENMAX_JPEG_DECODER** decoder) {
		*decoder = malloc(sizeof(OPENMAX_JPEG_DECODER));
		
		if (decoder[0] == NULL) {
			perror("malloc decoder");
			return OMXJPEG_ERROR_MEMORY;
			
		}
		
		memset(*decoder, 0, sizeof(OPENMAX_JPEG_DECODER));
		
		if ((decoder[0]->client = ilclient_init()) == NULL) {
			perror("ilclient_init");
			return OMXJPEG_ERROR_ILCLIENT_INIT;
			
		}

		if (OMX_Init() != OMX_ErrorNone) {
			ilclient_destroy(pDecoder[0]->client);
			perror("OMX_Init");
			
			return OMXJPEG_ERROR_OMX_INIT;
			
		}
		
		int error_code = prepareImageDecoder(pDecoder[0]);
		if (error_code != OMXJPEG_OK) return error_code;

		error_code = prepareResizer(pDecoder[0]);
		if (error_code != OMXJPEG_OK) return error_code;

		error_code = startupImageDecoder(pDecoder[0]);
		if (error_code != OMXJPEG_OK) return error_code;

		return OMXJPEG_OK;
		
	}
	
	int decode_image(OPENMAX_JPEG_DECODER* decoder, char* source_image, size_t image_size) {
		char* source_offset = source_image;
		size_t bytes_left = image_size;
		
		unsigned char is_buffer_filled = 0;
		buffer_index = 0;

		while (bytes_left > 0) {
			OMX_BUFFERHEADERTYPE* buffer_header = decoder->pp_input_buffer_header[buffer_index];
			buffer_index++;
			
			if (buffer_index >= decoder->input_buffer_header_count) {
				buffer_index = 0;
				
			}
			
			if (bytes_left > buffer_header->nAllocLen) buffer_header->nFilledLen = buffer_header->nAllocLen;
			else buffer_header->nFilledLen = bytes_left;

			bytes_left = bytes_left - buffer_header->nFilledLen;
			memcpy(buffer_header->pBuffer, source_offset, buffer_header->nFilledLen);

			source_offset = source_offset + buffer_header->nFilledLen;
		
			buffer_header->nOffset = 0;
			buffer_header->nFlags = 0;
			
			if (bytes_left <= 0) {
				buffer_header->nFlags = OMX_BUFFERFLAG_EOS;
				
			}
		
			int error_code = OMX_EmptyThisBuffer(decoder->image_decoder->handle, buffer_header);

			if (error_code != OMX_ErrorNone) {
				perror("Empty input buffer");
				fprintf(stderr, "Error code %x\n", error_code);
				
				return OMXJPEG_ERROR_MEMORY;
				
			}

			int done = 0;
			while (done == 0 && decoder->p_output_buffer_header == NULL) {
				if (decoder->p_output_buffer_header == NULL) {
					error_code = ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventPortSettingsChanged, decoder->image_decoder->out_port, 0, 0, 1, 0, 5);
					
					if (error_code == 0) {
						error_code = portSettingsChanged(decoder);
						
						if (error_code != OMXJPEG_OK) {
							return error_code;
							
						}
						
					}
					
				} else {
					error_code = ilclient_remove_event(decoder->image_decoder->component, OMX_EventPortSettingsChanged, decoder->image_decoder->out_port, 0, 0, 1);
					
					if (error_code == 0) {
						port_settings_changed_again(decoder);

					}
					
				}

				if (buffer_header->nFilledLen == 0) {
					done = 1;
					
				} if (done == 0 || decoder->p_output_buffer_header == NULL) {
					sleep(1);
					
				}
					
			}

			if ((is_buffer_filled == 0) && (decoder->p_output_buffer_header != NULL)) {
				error_code = OMX_FillThisBuffer(decoder->image_resizer->handle, decoder->p_output_buffer_header);
				
				if (error_code != OMX_ErrorNone) {
					perror("Filling output buffer");
					fprintf(stderr, "Error code %x\n", error_code);
					
					return OMXJPEG_ERROR_MEMORY;
					
				}

				is_buffer_filled = 1;
			
			}
		
		}

		int error_code = ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventBufferFlag, decoder->image_decoder->out_port, 1, OMX_BUFFERFLAG_EOS, 1, 0, 2);
		
		if (error_code != 0) {
			fprintf(stderr, "No EOS event on image decoder %d\n", ret);
			
		}
		
		error_code = ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventBufferFlag, decoder->image_resizer->out_port, 1, OMX_BUFFERFLAG_EOS, 1, 0, 2);
		
		if (error_code != 0) {
			fprintf(stderr, "No EOS event on image resizer %d\n", ret);
			
		}
		
		return OMXJPEG_OK;
		
	}

	void decoder_cleanup(OPENMAX_JPEG_DECODER* decoder) {
		OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandFlush, decoder->image_decoder->out_port, NULL);
		
		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandFlush, 0, decoder->image_decoder->out_port, 0, 0, TIMEOUT_MS);
		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandFlush, decoder->image_resizer->in_port, NULL);
		
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandFlush, 0, decoder->image_resizer->in_port, 1, 0, TIMEOUT_MS);
		OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandPortDisable, decoder->image_decoder->in_port, NULL);

		int i = 0;
		for (i = 0; i < decoder->inputBufferHeaderCount; i++) {
			OMX_BUFFERHEADERTYPE* buffer_header = decoder->pp_input_buffer_header[i];
			OMX_FreeBuffer(decoder->image_decoder->handle, decoder->image_decoder->in_port, buffer_header);
			
		}

		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandPortDisable, 0, decoder->image_decoder->in_port, 0, 0, TIMEOUT_MS);
		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandPortDisable, decoder->image_resizer->out_port, NULL);
		
		OMX_FreeBuffer(decoder->image_resizer->handle, decoder->image_resizer->out_port, decoder->p_output_buffer_header);
		
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandPortDisable, 0, decoder->image_resizer->out_port, 0, 0, TIMEOUT_MS);
		OMX_SendCommand(decoder->image_decoder->handle, OMX_CommandPortDisable, decoder->image_decoder->out_port, NULL);
		
		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandPortDisable, 0, decoder->image_decoder->out_port, 0, 0, TIMEOUT_MS);
		OMX_SendCommand(decoder->image_resizer->handle, OMX_CommandPortDisable, decoder->image_resizer->in_port, NULL);
		
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandPortDisable, 0, decoder->image_resizer->in_port, 0, 0, TIMEOUT_MS);
		
		OMX_SetupTunnel(decoder->image_decoder->handle, decoder->image_decoder->out_port, NULL, 0);
		OMX_SetupTunnel(decoder->image_resizer->handle, decoder->image_resizer->in_port, NULL, 0);
		
		ilclient_change_component_state(decoder->image_decoder->component, OMX_StateIdle);
		ilclient_change_component_state(decoder->image_resizer->component, OMX_StateIdle);

		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandStateSet, 0, OMX_StateIdle, 0, 0, TIMEOUT_MS);
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandStateSet, 0, OMX_StateIdle, 0, 0, TIMEOUT_MS);

		ilclient_change_component_state(decoder->image_decoder->component, OMX_StateLoaded);
		ilclient_change_component_state(decoder->image_resizer->component, OMX_StateLoaded);

		ilclient_wait_for_event(decoder->image_decoder->component, OMX_EventCmdComplete, OMX_CommandStateSet, 0, OMX_StateLoaded, 0, 0, TIMEOUT_MS);
		ilclient_wait_for_event(decoder->image_resizer->component, OMX_EventCmdComplete, OMX_CommandStateSet, 0, OMX_StateLoaded, 0, 0, TIMEOUT_MS);

		OMX_Deinit();

		if (decoder->client != NULL) {
			ilclient_destroy(decoder->client);
			
		}
		
	}
	
	/*int
	main(int argc, char *argv[])
	{
		OPENMAX_JPEG_DECODER *pDecoder;
		char *sourceImage;
		size_t imageSize;
		int s;
		if (argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
		}
		FILE *fp = fopen(argv[1], "rb");
		if (!fp) {
		printf("File %s not found.\n", argv[1]);
		}
		fseek(fp, 0L, SEEK_END);
		imageSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		sourceImage = malloc(imageSize);
		assert(sourceImage != NULL);
		s = fread(sourceImage, 1, imageSize, fp);
		assert(s == imageSize);
		fclose(fp);
		bcm_host_init();
		s = setupOpenMaxJpegDecoder(&pDecoder);
		assert(s == 0);
		s = decodeImage(pDecoder, sourceImage, imageSize);
		assert(s == 0);
		cleanup(pDecoder);
		free(sourceImage);
		return 0;
	}*/
	
#endif


