function sff_fast(N, q, combo, samples)
    t = logspace(-1,4);
    zt = zeros(1,numel(t)) + 1i*zeros(1,numel(t));
    for c = 1:samples
        h = SYK(N, q, combo);
        lambda = eig(h);
        for i = 1:numel(lambda)    
            zt = zt + exp(t.*complex(0,1)*lambda(i));
        end
        disp(c);
    end
    sff = (zt.*conj(zt))./samples;
    hold off
    loglog(t,sff);
end