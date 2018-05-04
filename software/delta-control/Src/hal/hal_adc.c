/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_adc.h"
#include "hal_dma.h"

#include "qassert.h"
#include "app_config.h"
#include "average_short.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ------------------------- Average ---------------------------------------- */

typedef struct
{
    bool     running;
    bool     done;
    uint16_t tick;
    uint16_t rate;
} HalAdcState_t;

PRIVATE uint16_t       adc_rate[HAL_ADC_INPUT_NUM];
PRIVATE uint8_t        adc_enabled[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_dma[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_channels[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_peaks[HAL_ADC_INPUT_NUM];
PRIVATE AverageShort_t adc_averages[HAL_ADC_INPUT_NUM];

PRIVATE HalAdcState_t  hal_adc1;

/* ------------------------- Functions -------------------------------------- */

PUBLIC void
hal_adc_init( void )
{
	memset( &hal_adc1,     0, sizeof( hal_adc1 ) );
	memset( &adc_peaks,    0, sizeof( adc_peaks ) );
	memset( &adc_rate,     0, sizeof( adc_rate ) );
	memset( &adc_enabled,  0, sizeof( adc_enabled ) );
	memset( &adc_dma,      0, sizeof( adc_dma ) );
	memset( &adc_channels, 0, sizeof( adc_channels ) );
	memset( &adc_averages, 0, sizeof( adc_averages ) );

	average_short_init( &adc_averages[HAL_ADC_INPUT_VREFINT], 32 );

	average_short_init( &adc_averages[HAL_ADC_INPUT_M1_CURRENT],  32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_M2_CURRENT],  32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_M3_CURRENT],  32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_M4_CURRENT],  32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_VOLT_SENSE],  32 );

	average_short_init( &adc_averages[HAL_ADC_INPUT_TEMP_PCB],    32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_TEMP_REG],    32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_TEMP_EXT],    32 );
	average_short_init( &adc_averages[HAL_ADC_INPUT_TEMP_INTERNAL], 32 );

	//start cubemx generated adc setup

	ADC_ChannelConfTypeDef sConfig;

	    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	    */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = DISABLE;
	  hadc1.Init.ContinuousConvMode = ENABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 10;
	  hadc1.Init.DMAContinuousRequests = ENABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_15;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_14;
	  sConfig.Rank = 2;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_7;
	  sConfig.Rank = 3;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_6;
	  sConfig.Rank = 4;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_13;
	  sConfig.Rank = 5;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_10;
	  sConfig.Rank = 6;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_11;
	  sConfig.Rank = 7;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_12;
	  sConfig.Rank = 8;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	  sConfig.Rank = 9;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_VREFINT;
	  sConfig.Rank = 10;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  //end cubemx adc setup



}

/* -------------------------------------------------------------------------- */

PUBLIC bool
hal_adc_valid( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return adc_averages[input].counter > 0;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return (uint32_t)average_short_get_last( &adc_averages[input] );
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read_avg( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return (uint32_t)average_short_get_average( &adc_averages[input] );
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read_peak( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return adc_peaks[input];
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_adc_start( HalAdcInput_t input, uint16_t poll_rate_ms )
{
    /* Increment reference count for this input */
    adc_enabled[input] = (uint8_t)(adc_enabled[input] + 1);

    /* Clear the peak history */
    adc_peaks[input] = 0;

    /* Set the interval to poll this */
    adc_rate[input] = poll_rate_ms;

    /* Check if ADC1 needs enabling */
    bool enabled = false;
    hal_adc1.rate = UINT16_MAX;
    for( uint8_t chan = HAL_ADC_INPUT_M1_CURRENT;
                 chan < HAL_ADC_INPUT_VREFINT;
                 chan++ )
    {
        if( adc_enabled[chan] > 0 )
        {
            hal_adc1.rate = MIN( hal_adc1.rate, adc_rate[chan] );
            enabled |= true;
        }
    }

    if( !hal_adc1.running && enabled )
    {
        hal_adc1.running = true;
        hal_adc1.done    = true;   /* Allow first conversion */
    }

}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_adc_stop( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );

    /* Decrement reference count for this input */
    if( adc_enabled[input] > 0 )
    {
        adc_enabled[input] = (uint8_t)(adc_enabled[input] - 1);
    }

    /* If channel is OFF, scan for ADC controller to switch off */
    if( adc_enabled[input] == 0 )
    {
        /* ADC 1 */
        bool enabled = false;
        for( uint8_t chan = HAL_ADC_INPUT_M1_CURRENT;
                     chan < HAL_ADC_INPUT_VREFINT;
                     chan++ )
        {
            if( adc_enabled[chan] > 0 )
            {
                enabled = true;
                break;
            }
        }

        /* If no longer enabled, turn off the sampling DMA */
        if( !enabled )
        {
            hal_adc1.running = false;
            HAL_ADC_Stop_DMA( &hadc1 );
        }

    }
}

/* -------------------------------------------------------------------------- */

/** Timer tick to trigger a ADC conversion cycle */

PUBLIC void
hal_adc_tick( void )
{
    /* ADC 1 */
    if( hal_adc1.running )
    {
        if( hal_adc1.done )
        {
            hal_adc1.tick++;
            if( hal_adc1.tick > hal_adc1.rate )
            {
                hal_adc1.tick = 0;
                HAL_ADC_Stop_DMA( &hadc1 );
                HAL_ADC_Start_DMA( &hadc1, &adc_dma[HAL_ADC_INPUT_M1_CURRENT], HAL_ADC_INPUT_NUM );
                hal_adc1.done = false;
            }
        }
    }

}

/* -------------------------------------------------------------------------- */

void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
    if( hadc == &hadc1 )
    {
        /* Freeze the DMA collected samples */
        memcpy( &adc_channels[HAL_ADC_INPUT_M1_CURRENT],
                &adc_dma[HAL_ADC_INPUT_M1_CURRENT],
				HAL_ADC_INPUT_NUM * sizeof( adc_channels[0] ) );

        /* Run them though the averaging */
        for( uint8_t chan = HAL_ADC_INPUT_M1_CURRENT;
                     chan < HAL_ADC_INPUT_VREFINT;
                     chan++ )
        {
            average_short_update( &adc_averages[chan], (uint16_t)adc_channels[chan] );
            adc_peaks[chan] = MAX( adc_peaks[chan], adc_channels[chan] );
        }
        hal_adc1.done = true;
    }

}

/* -------------------------------------------------------------------------- */

void HAL_ADC_ErrorCallback( ADC_HandleTypeDef* hadc __attribute__((unused)) )
{
    //asm("nop");
}


void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(adcHandle->Instance==ADC1)
  {
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    */
    GPIO_InitStruct.Pin = TEMP_PCB_Pin|TEMP_EXT_0_Pin|TEMP_EXT_1_Pin|V_SENSE_Pin
                          |MOTOR_2_CURRENT_Pin|MOTOR_1_CURRENT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MOTOR_4_CURRENT_Pin|MOTOR_3_CURRENT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(adcHandle, DMA_Handle, hdma_adc1);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
  if(adcHandle->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    */
    HAL_GPIO_DeInit(GPIOC, TEMP_PCB_Pin|TEMP_EXT_0_Pin|TEMP_EXT_1_Pin|V_SENSE_Pin
                          |MOTOR_2_CURRENT_Pin|MOTOR_1_CURRENT_Pin);

    HAL_GPIO_DeInit(GPIOA, MOTOR_4_CURRENT_Pin|MOTOR_3_CURRENT_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  }
}


/* ----- End ---------------------------------------------------------------- */
