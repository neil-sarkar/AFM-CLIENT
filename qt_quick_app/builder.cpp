#include "builder.h"
#include "afm.h"
#include "dac.h"
#include "adc.h"
#include "pga.h"

Builder::Builder() {}

AFM* Builder::build_afm() {
    // Create the collection of DACs
    QHash<QString, DAC*> dac_collection;
    dac_collection["buffered_1"] = new DAC(0);
    dac_collection["buffered_2"] = new DAC(1);
    dac_collection["board_2"] = new DAC(2);
    dac_collection["z_amplitude"] = new DAC(3);
    dac_collection["board_1"] = new DAC(4);
    dac_collection["buffered_3"] = new DAC(5);
    dac_collection["z_offset_fine"] = new DAC(6);
    dac_collection["y_1"] = new DAC(7);
    dac_collection["z_offset_coarse"] = new DAC(8);
    dac_collection["y_2"] = new DAC(9);
    dac_collection["x_1"] = new DAC(10);
    dac_collection["x_2"] = new DAC(11);

    // Create the collection of ADC
    QHash<QString, ADC*> adc_collection;
    adc_collection["z_piezoresistor_amplitude"] = new ADC(5);
    adc_collection["phase"] = new ADC(6);

    // PGA
    QHash<QString, PGA*> pga_collection;
    pga_collection["x_1"] = new PGA(1);
    pga_collection["x_2"] = new PGA(2);
    pga_collection["y_1"] = new PGA(3);
    pga_collection["y_2"] = new PGA(4);
    pga_collection["z_fine"] = new PGA(5);
    pga_collection["dds_amplitude"] = new PGA(6);
    pga_collection["z_coarse"] = new PGA(7);
    pga_collection["leveling"] = new PGA(8);

    Motor* motor = new Motor();
    PID* pid = new PID();

    return new AFM(pga_collection, dac_collection, adc_collection, motor, pid);
}
//ADC_X1 3
//ADC_X2 7
//ADC_Y1 6
//ADC_Y2 8
//ADC_Z 2
//ADC_Z_PZR_AMP 5
//ADC_PHASE 0


