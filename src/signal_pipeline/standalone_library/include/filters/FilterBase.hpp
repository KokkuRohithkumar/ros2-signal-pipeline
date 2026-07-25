#ifndef FILTERBASE_HPP
#define FILTERBASE_HPP

template<typename T>
class FilterBase
{
public:

    virtual T update(T sample,double dt)=0;

    virtual void reset()=0;

    virtual ~FilterBase()=default;
};

#endif
