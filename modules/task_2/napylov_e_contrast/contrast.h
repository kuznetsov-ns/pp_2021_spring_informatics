// Copyright 2021 Napylov Evgenii
#ifndef MODULES_TASK_2_NAPYLOV_E_CONTRAST_CONTRAST_H_
#define MODULES_TASK_2_NAPYLOV_E_CONTRAST_CONTRAST_H_

#include <omp.h>
#include <vector>


typedef std::vector<unsigned char> VecImage;

void print_vec(const VecImage& vec);

VecImage RandomVector(int size);

VecImage add_contrast(VecImage image);

VecImage add_contrast_omp(VecImage image);

#endif  // MODULES_TASK_2_NAPYLOV_E_CONTRAST_CONTRAST_H_
