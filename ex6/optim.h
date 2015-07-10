// CLOSE THE FILE AND DONT LOOK AT IT
// NOW! NEVER!
// BOOOOOO

typedef struct fparam_s {
    vector<double> x_in;
    vector<double> y_in;
} fparam_t;


double fitfun1_helper(double a, double b, vector<double> const & x_in, vector<double> const & y_in)
{
    double sse = 0.0;
    vector<double> model_eval;
    vector<double> residuals;

    for(int i=0; i<x_in.size(); i++)
    {
        model_eval.push_back(a+b*x_in[i]);
    }

    for(int i=0; i<y_in.size(); i++)
    {
        residuals.push_back(pow(model_eval[i]-y_in[i],2));
    }

    sse = std::accumulate(residuals.begin(),residuals.end(),0.0);
    return sse;
}

double fitfun1(const gsl_vector *v, void *param)
{
    fparam_t *fp = (fparam_t *) param;

    vector<double> const & x_in  = fp->x_in;
    vector<double> const & y_in = fp->y_in;

    double a = gsl_vector_get(v, 0);
    double b = gsl_vector_get(v, 1);
    return fitfun1_helper(a, b, x_in, y_in);
}

double fitfun2_helper(double a, double b, vector<double> const & x_in, vector<double> const & y_in)
{
    double sse = 0.0;
    vector<double> model_eval;
    vector<double> residuals;

    for(int i=0; i<x_in.size(); i++)
    {
        model_eval.push_back(a*exp(b*x_in[i]));
    }

    for(int i=0; i<y_in.size(); i++)
    {
        residuals.push_back(pow(model_eval[i]-y_in[i],2));
    }

    sse = std::accumulate(residuals.begin(),residuals.end(),0.0);
    return sse;
}

// Official fmin function called from fminsearch
double fitfun2(const gsl_vector *v, void *param)
{
    fparam_t *fp = (fparam_t *) param;

    vector<double> const & x_in  = fp->x_in;
    vector<double> const & y_in = fp->y_in;

    double a = gsl_vector_get(v, 0);
    double b = gsl_vector_get(v, 1);
    return fitfun2_helper(a, b, x_in, y_in);
}


double fitfun3_helper(double a, double b, double c, double d, vector<double> const & x_in, vector<double> const & y_in)
{
    double sse = 0.0;
    vector<double> model_eval;
    vector<double> residuals;

    for(int i=0; i<x_in.size(); i++)
    {
        model_eval.push_back(a /(1+exp(b*(c-x_in[i])))+d );
    }

    for(int i=0; i<y_in.size(); i++)
    {
        residuals.push_back(pow(model_eval[i]-y_in[i],2));
    }

    sse = std::accumulate(residuals.begin(),residuals.end(),0.0);

    if(a<0 || b<0 || c<0 || d<0)
    {
        // WHIPLASH
        sse = sse + 5000*abs(a);
    }

    return sse;
}

// Official fmin function called from fminsearch
double fitfun3(const gsl_vector *v, void *param)
{
    fparam_t *fp = (fparam_t *) param;

    vector<double> const & x_in  = fp->x_in;
    vector<double> const & y_in = fp->y_in;

    double a = gsl_vector_get(v, 0);
    double b = gsl_vector_get(v, 1);
    double c = gsl_vector_get(v, 2);
    double d = gsl_vector_get(v, 3);

    return fitfun3_helper(a, b, c, d, x_in, y_in);
}

void interpolate(
    // input:
    int fitnum,
    vector<double> const & x_in,
    vector<double> const & y_in,
    vector<double> const & x_out,
    // output:
    vector<double> & y_out
    )
{
    int dim;
    double step;
    double coef[4];
    gsl_multimin_function minex_func;

    // Starting point
    switch(fitnum)
    {
        case 1:
            coef[0] = 0.05;
            coef[1] = 0.05;
            step = 0.1;
            dim = 2;
            minex_func.f = fitfun1;
            break;

        case 2:
            coef[0] = 0.05;
            coef[1] = 0.05;
            step = 0.001;
            dim = 2;
            minex_func.f = fitfun2;
            break;

        case 3:
            coef[0] = 4.0;
            coef[1] = 1.0;
            coef[2] = 50.0;
            coef[3] = 0.1;
            step = 1.0;
            dim = 4;
            minex_func.f = fitfun3;
            break;
    }

    gsl_vector * x = gsl_vector_alloc(dim);
    for(int i=0; i<dim; ++i)
        gsl_vector_set(x, i, coef[i]);

    // Set initial step sizes
    gsl_vector * ss = gsl_vector_alloc(dim);
    gsl_vector_set_all(ss, step);

    // Initialize method and iterate
    fparam_t fp;
    fp.x_in = x_in;
    fp.y_in = y_in;

    minex_func.n = dim;
    minex_func.params = &fp;

    const gsl_multimin_fminimizer_type * T = gsl_multimin_fminimizer_nmsimplex2;
    gsl_multimin_fminimizer * s = gsl_multimin_fminimizer_alloc(T, dim);
    gsl_multimin_fminimizer_set(s, &minex_func, x, ss);

    // USER input
    size_t iter = 0, max_iter = 500000;
    double Tol = 0.00000001;
    int Display = 0;
    int conv = 0;
    int status;
    do {
        iter++;
        status = gsl_multimin_fminimizer_iterate(s);

        if(status)
            break;

        double size = gsl_multimin_fminimizer_size(s);
        status = gsl_multimin_test_size(size, Tol);

        if(status == GSL_SUCCESS)
        {
            conv = 1;
            if(Display)
                printf("converged to minimum at\n");
        }

        if(Display)
        {
            cout << "Iteration " << iter << ": ";
            for(int i=0; i<dim; ++i)
                cout << gsl_vector_get(s->x, i) << " ";
            cout << "f() = " << s->fval << " size = " << size << endl;
        }

    } while(status == GSL_CONTINUE && iter < max_iter);

    // Hopefully converged
    if(conv)
    {
        for(int i=0; i<dim; ++i)
            coef[i] = gsl_vector_get(s->x, i);
    }
    else
    {
        cout << "The optimisation didn't converge, stop." << endl;
        return;
    }

    gsl_vector_free(x);
    gsl_vector_free(ss);
    gsl_multimin_fminimizer_free(s);

    switch(fitnum)
    {
    case 1:
        for(int i=0; i<y_out.size(); ++i)
            y_out[i] = coef[0]+coef[1]*x_out[i];
        break;

    case 2:
        for(int i=0; i<y_out.size(); ++i)
            y_out[i] = coef[0]*exp(coef[1]*x_out[i]);
        break;

    case 3:
        for(int i=0; i<y_out.size(); ++i)
            y_out[i] = coef[0] / ( 1+exp( coef[1]*(coef[2]-x_out[i]) ) ) + coef[3];
        break;
    }
}
