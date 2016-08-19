/*
 * Copyright (C) 2015 Altera Corporation
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include "dynamic_clock_regs.h"

/* prototypes */
static struct platform_driver the_platform_driver;

/* globals */

static int g_dynamic_clock_driver_base_addr;
static int g_dynamic_clock_driver_base_size;
static void *g_dynamic_clock_base;
static struct semaphore g_dev_probe_sem;
static spinlock_t g_clock_lock;


static ssize_t parameters_show(struct device_driver *driver, char *buf)
{
  uint32_t m_high, m_low, m_bypass, m_odd;
  uint32_t n_high, n_low, n_bypass, n_odd;
  uint32_t c_high, c_low, c_bypass, c_odd;
  uint32_t bandwidth, vco_div, c_pump;
  unsigned long flags; //what should this be


   spin_lock_irqsave(&g_clock_lock, flags);
   m_high = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_OFST) & ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_MSK;
   m_low  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_OFST) & ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_MSK;
   m_bypass  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_OFST) & ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_MSK;
   m_odd  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_OFST) & ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_MSK;

   n_high = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_OFST) & ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_MSK;
   n_low  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_OFST) & ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_MSK;
   n_bypass  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_OFST) & ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_MSK;
   n_odd  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_OFST) & ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_MSK;

   c_high = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_C0_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_OFST) & ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_MSK;
   c_low  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_C0_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_OFST) & ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_MSK;
   c_bypass  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_C0_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_OFST) & ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_MSK;
   c_odd  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_C0_COUNTER(g_dynamic_clock_base))) >> ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_OFST) & ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_MSK;

   bandwidth = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_BANDWIDTH(g_dynamic_clock_base)))  >> ALTERA_DYNAMIC_CLOCK_BANDWIDTH_OFST) & ALTERA_DYNAMIC_CLOCK_BANDWIDTH_MSK;
   vco_div  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_VCO_DIV(g_dynamic_clock_base)))  >> ALTERA_DYNAMIC_CLOCK_VCO_DIV_OFST) & ALTERA_DYNAMIC_CLOCK_VCO_DIV_MSK;
   c_pump  = ((ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_C_PUMP(g_dynamic_clock_base)))  >> ALTERA_DYNAMIC_CLOCK_C_PUMP_OFST) & ALTERA_DYNAMIC_CLOCK_C_PUMP_MSK;
   spin_unlock_irqrestore(&g_clock_lock, flags);


   return scnprintf(buf, PAGE_SIZE,
		    "m_high: %d\n"
		    "m_low:  %d\n"
		    "m_bypass: %d\n"
		    "m_odd: %d\n"
		    "n_high: %d\n"
		    "n_low:  %d\n"
		    "n_bypass: %d\n"
		    "n_odd: %d\n"
		    "c_high: %d\n"
		    "c_low:  %d\n"
		    "c_bypass: %d\n"
		    "c_odd: %d\n"
		    "bandwidth %d\n"
		    "vco_dev %d\n"
		    "c_pump %d\n"
		    ,m_high
		    ,m_low
		    ,m_bypass
		    ,m_odd
		    ,n_high
		    ,n_low
		    ,n_bypass
		    ,n_odd
		    ,c_high
		    ,c_low
		    ,c_bypass
		    ,c_odd
		    ,bandwidth
		    ,vco_div
		    ,c_pump);
}


static ssize_t parameters_store(struct device_driver *driver, const char *buf, size_t count)
{

  uint32_t m_high, m_low, m_bypass, m_odd;
  uint32_t n_high, n_low, n_bypass, n_odd;
  uint32_t c_high, c_low, c_bypass, c_odd;
  uint32_t bandwidth, vco_div, c_pump;
 
  char *value;
  char string_value[strlen(buf)];
  char *string_pt = string_value;
  unsigned long value_array[15];
  int i = 0;
  int result;
  unsigned long flags; //what should this be

  uint32_t count_value = 0;
  
  strcpy(string_value,buf);
  while((value=strsep(&string_pt, " ")) != NULL){
    //add some protection for i here
    result = kstrtoul(value, 0, &(value_array[i++]));
    if(result != 0)
      return -EINVAL;
  }

  m_high = value_array[0];
  //pr_info("m_high: %u\n", m_high);

  m_low = value_array[1];
  //pr_info("m_low: %u\n", m_low);

  m_bypass = value_array[2];
  //pr_info("m_bypass: %u\n", m_bypass);

  m_odd = value_array[3];
  //pr_info("m_odd: %u\n", m_odd);

  n_high = value_array[4];
  //pr_info("n_high: %u\n", n_high);

  n_low = value_array[5];
  //pr_info("n_low: %u\n", n_low);

  n_bypass = value_array[6];
  //pr_info("n_bypass: %u\n", n_bypass);

  n_odd = value_array[7];
  //pr_info("n_odd: %u\n", n_odd);
  
  c_high = value_array[8];
  //pr_info("c_high: %u\n", c_high);

  c_low = value_array[9];
  //pr_info("c_low: %u\n", c_low);

  c_bypass = value_array[10];
  //pr_info("c_bypass: %u\n", c_bypass);

  c_odd = value_array[11];
  //pr_info("c_odd: %u\n", c_odd);

  bandwidth = value_array[12];
  //pr_info("bandwidth: %u\n", bandwidth);

  vco_div = value_array[13];
  //pr_info("vco_div: %u\n", vco_div);

  c_pump = value_array[14];
  //pr_info("c_pump: %u\n", c_pump);

  spin_lock_irqsave(&g_clock_lock, flags);

  count_value = 0;
  count_value  |=  ((m_high & ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_MSK) << ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_OFST);
  count_value  |=  ((m_low & ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_MSK) << ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_OFST);
  count_value  |=  ((m_bypass & ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_MSK) << ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_OFST);
  count_value  |=  ((m_odd & ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_MSK) << ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_OFST);
  iowrite32(count_value, IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(g_dynamic_clock_base));

  count_value = 0;
  count_value  |=  ((n_high & ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_MSK) << ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_OFST);
  count_value  |=  ((n_low & ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_MSK) << ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_OFST);
  count_value  |=  ((n_bypass & ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_MSK) << ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_OFST);
  count_value  |=  ((n_odd & ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_MSK) << ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_OFST);
  iowrite32(count_value, IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(g_dynamic_clock_base));

  count_value = 0;
  count_value  |=  ((c_high & ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_MSK) << ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_OFST);
  count_value  |=  ((c_low & ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_MSK) << ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_OFST);
  count_value  |=  ((c_bypass & ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_MSK) << ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_OFST);
  count_value  |=  ((c_odd & ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_MSK) << ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_OFST);
  iowrite32(count_value, IOADDR_ALTERA_DYNAMIC_CLOCK_C_COUNTER(g_dynamic_clock_base));

  iowrite32(bandwidth, IOADDR_ALTERA_DYNAMIC_CLOCK_BANDWIDTH(g_dynamic_clock_base));

  iowrite32(vco_div, IOADDR_ALTERA_DYNAMIC_CLOCK_VCO_DIV(g_dynamic_clock_base));
  iowrite32(c_pump, IOADDR_ALTERA_DYNAMIC_CLOCK_C_PUMP(g_dynamic_clock_base));

  iowrite32(0, IOADDR_ALTERA_DYNAMIC_CLOCK_START(g_dynamic_clock_base));
  
  spin_unlock_irqrestore(&g_clock_lock, flags);

  return count;
}

DRIVER_ATTR(parameters, (S_IRUGO|S_IWUSR|S_IWGRP), parameters_show, parameters_store);


static ssize_t frequency_show(struct device_driver *driver, char *buf)
{
  unsigned long flags;
  uint32_t frequency;

  spin_lock_irqsave(&g_clock_lock, flags);
  frequency = (ioread32(IOADDR_ALTERA_DYNAMIC_FREQ(g_dynamic_clock_base))
	       >> ALTERA_DYNAMIC_CLOCK_FREQ_OFST) & ALTERA_DYNAMIC_CLOCK_FREQ_MSK;
  spin_unlock_irqrestore(&g_clock_lock, flags);

  return scnprintf(buf, PAGE_SIZE, "%d\n", frequency);
}
DRIVER_ATTR(frequency, (S_IRUGO), frequency_show, NULL);


static ssize_t lock_status_show(struct device_driver *driver, char *buf)
{
  unsigned long flags;
  uint32_t status;
  char status_char[16];
  
  spin_lock_irqsave(&g_clock_lock, flags);
  status = (ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_LOCK(g_dynamic_clock_base))
	       >> ALTERA_DYNAMIC_CLOCK_LOCK_OFST) & ALTERA_DYNAMIC_CLOCK_LOCK_MSK;
  spin_unlock_irqrestore(&g_clock_lock, flags);

  (status == ALTERA_DYNAMIC_CLOCK_LOCKED)?strcpy(status_char, "Locked\n"):strcpy(status_char,"Not Locked\n");
  return scnprintf(buf, PAGE_SIZE, "%s\n", status_char);
}
DRIVER_ATTR(lock_status, (S_IRUGO), lock_status_show, NULL);



static ssize_t reconfig_status_show(struct device_driver *driver, char *buf)
{
  unsigned long flags;
  uint32_t status;
  char status_char[7];
  
  spin_lock_irqsave(&g_clock_lock, flags);
  status = (ioread32(IOADDR_ALTERA_DYNAMIC_CLOCK_STATUS(g_dynamic_clock_base))
	       >> ALTERA_DYNAMIC_CLOCK_STATUS_OFST) & ALTERA_DYNAMIC_CLOCK_STATUS_MSK;
  spin_unlock_irqrestore(&g_clock_lock, flags);

  (status == ALTERA_DYNAMIC_CLOCK_STATUS_READY)?strcpy(status_char, "Ready\n"):strcpy(status_char,"Busy\n");
  return scnprintf(buf, PAGE_SIZE, "%s\n", status_char);
}
DRIVER_ATTR(reconfig_status, (S_IRUGO), reconfig_status_show, NULL);

static int platform_probe(struct platform_device *pdev)
{
  int ret_val;
  struct resource *r;

  pr_info("enter platform_probe\n");
  
  if (down_interruptible(&g_dev_probe_sem))
    return -ERESTARTSYS;

  spin_lock_init(&g_clock_lock);
  
  r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
  if (r == NULL) {
    dev_err(&pdev->dev, "IORESOURCE_MEM, 0 does not exist\n");
    return -ENODEV;
  }

  g_dynamic_clock_driver_base_addr = r->start;
  g_dynamic_clock_driver_base_size = resource_size(r);

  g_dynamic_clock_base = devm_ioremap(&pdev->dev,
				      g_dynamic_clock_driver_base_addr,
				      g_dynamic_clock_driver_base_size);

  if(g_dynamic_clock_base == NULL){
      dev_err(&pdev->dev, "Error requestion io memory for dynamic clock driver\n");
      return -ENODEV;
  }

  //set the reconfig ip up in polling mode
  //polling mode seems to hang status... so far I think we can get away without it
  //  iowrite32((ALTERA_DYNAMIC_CLOCK_POLL_MODE >> ALTERA_DYNAMIC_CLOCK_MODE_OFST) & ALTERA_DYNAMIC_CLOCK_MODE_MSK,  IOADDR_ALTERA_DYNAMIC_CLOCK_MODE(g_dynamic_clock_base));
  
  ret_val = driver_create_file(&the_platform_driver.driver,
			       &driver_attr_parameters);
  if (ret_val != 0) {
    dev_err(&pdev->dev, "failed to create pll parameters sysfs entry\n");
  }
  
  ret_val = driver_create_file(&the_platform_driver.driver,
			       &driver_attr_frequency);
  if (ret_val != 0) {
    pr_err("failed to create frequency sysfs entry");
  }

  /*  ret_val = driver_create_file(&the_platform_driver.driver,
			       &driver_attr_reconfig_status);
  if (ret_val != 0) {
    pr_err("failed to create pll reconfig status sysfs entry");
    }*/


  ret_val = driver_create_file(&the_platform_driver.driver,
			       &driver_attr_lock_status);
  if (ret_val != 0) {
    pr_err("failed to create pll lock status sysfs entry");
  }
  up(&g_dev_probe_sem);
  pr_info("exit platform_probe\n");
  return 0;
}

static int platform_remove(struct platform_device *pdev)
{
  pr_info("enter platform_remove\n");

  driver_remove_file(&the_platform_driver.driver, &driver_attr_parameters);
  driver_remove_file(&the_platform_driver.driver,
		     &driver_attr_frequency);

  pr_info("exit platform_remove\n");
  return 0;
}

static struct of_device_id dynamic_clock_driver_dt_ids[] = {
	{
	  .compatible = "dynamic_clock,driver-1.0"},
	{ /* end of table */ }
};

MODULE_DEVICE_TABLE(of, dynamic_clock_driver_dt_ids);

static struct platform_driver the_platform_driver = {
	.probe = platform_probe,
	.remove = platform_remove,
	.driver = {
		   .name = "dynamic_clock",
		   .owner = THIS_MODULE,
		   .of_match_table = dynamic_clock_driver_dt_ids,
		   },
};

static int dynamic_clock_init(void)
{
	int ret_val;

	pr_info("enter dynamic_clock_init\n");
	sema_init(&g_dev_probe_sem, 1);

	ret_val = platform_driver_register(&the_platform_driver);
	if (ret_val != 0) {
		pr_err("platform_driver_register returned %d\n", ret_val);
		return ret_val;
	}

	pr_info("exit dynamic_clock_init\n");
	return 0;
}

static void dynamic_clock_exit(void)
{
  pr_info("enter dynamic_clock_exit \n");
  
  platform_driver_unregister(&the_platform_driver);
  
  pr_info("exit dynamic_clock_exit \n");
}

module_init(dynamic_clock_init);
module_exit(dynamic_clock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Howard Butler <hbutler@intel.com>");
MODULE_DESCRIPTION("Run Time Pll Output Clock Frequency Modification");
MODULE_VERSION("0.1");
