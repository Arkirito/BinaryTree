#pragma once

#define COMMON_CLASS_DEFINITION(ClassType, ParentType) using Super = ParentType<T>;

#define SAFE_DELEETE(Ptr) delete Ptr; Ptr = nullptr;