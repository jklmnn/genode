/*
 * \brief Test Ada dynamic dispatching
 * \author Johannes Kliemann
 * \date 2019-12-05
 *
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 * Copyright (C) 2019 Componolit GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/log.h>
#include <base/component.h>

extern "C" void run_dispatch(int *result);
extern "C" void adainit();

void Component::construct(Genode::Env &env)
{
	int result;
	adainit();
	Genode::log("Ada dispatch test");
	run_dispatch(&result);
	if(!result){
		Genode::log("Test succeeded");
	}else{
		Genode::log("Test failed");
	}
	env.parent().exit(result);
}
