run1 = 2; 
run2 = 65;

for run3 = 0:0       
for run4 = 1:12
for run5 = 1:1
        tfin = 20;
        NN = 1;
        
        parameter = -59 + (run4-1)*3;
        parameterA = 'V_{1/2hCaS} = '
        label = ' mV'
        parameter2 = 1 - (run3-1)*0.05;
        parameter2a = 'g_{Mod}'
        label2 = 'nS'
        
        
        
        
        xmax = 3
       
         % run=[num2str(Run) '_2'] 
        % VarN=[num2str(Dir2) '/V' num2str(run) '.dat']; 
        % f2=fopen(VarN); 
        % yy2=fread(f2,[NN, 10000000],'double')'; 
        % fclose(f2); 
        
        % run=[num2str(Run) '_3'] 
        % VarN=[num2str(Dir2) '/V' num2str(run) '.dat']; 
        % f3=fopen(VarN); 
        % yy3=fread(f3,[NN, 10000000],'double')'; 
        % fclose(f3);         .246437 0.414997517    0.5014    0.7068
        %if run5>3
        %    xmax = 5;
        %else
        %    xmax = 10.0;
        %end
        
        Dir1=[num2str(run1) '_' num2str(run2)]; 
        Dir2=[num2str(Dir1) '_' num2str(run3)]; 
        Run=[num2str(Dir2) '_' num2str(run4)]; 
        
        run11=[num2str(Run) '_' num2str(run5)]; 
        %run=[num2str(Run) '_1'] 
        VarN=[num2str(run1) 'code2neurons/code2/' num2str(Dir2) '/V' num2str(run11) '.dat']; 
        f1=fopen(VarN); 
        yy1=fread(f1,[2*NN, 10000000],'double')'; 
        fclose(f1);
        %bd = load([num2str(run1) 'code2neurons/code2/' num2str(Dir1) '/bursts2J' num2str(run) '.txt']);
        %bd1 = load([num2str(run1) 'code2neurons/code2/' num2str(Dir1) '/bursts1J' num2str(run) '.txt']);


         %run22=[num2str(Run) '_1'] 
         %VarN=[num2str(run1) 'code2neurons/code2/' num2str(Dir1) '/V' num2str(run22) '.dat']; 
         %f2=fopen(VarN); 
         %yy2=fread(f2,[2*NN, 10000000],'double')'; 
         %fclose(f2); 
        
         %run33=[num2str(Run) '_3'] 
         %VarN=[num2str(run1) 'code2neurons/code2/' num2str(Dir1) '/V' num2str(run33) '.dat']; 
         %f3=fopen(VarN); 
         %yy3=fread(f3,[2*NN, 10000000],'double')'; 
         %fclose(f3);       

        yy2 = zeros(2,2*NN);
        yy3 = zeros(266,2*NN);
        
        Vs = [yy1; yy2(2:end,:); yy3(2:end,:)];
         
        t = 0:0.0001:tfin;
        
 

            f = figure() 
        
        axes('Position', [0.1, 0.1, .9, 0.325]) 
            %plot((t(1:length(Vs(:,1)))),Vs(:,1))
            plot(t,Vs(1:length(t),2), 'r')
            hold on
            %plot(bd1(:,1), zeros(length(bd1),1))
            %plot([0 xmax], [-52.5 -52.5], 'g')
            xlabel('Neuron 2 (s)', 'fontsize',20)
            %ylabel('mV', 'FontSize',14)
            set(gca, 'FontSize', 20)
            axis([0 xmax -90 70])

	    axes('Position', [0.1, 0.6, .9, 0.325]) 
            %plot(t(1:length(Vs(:,2))),Vs(:,2))
            plot(t,Vs(1:length(t),1), 'b')
            hold on
            %plot([0 xmax], [-52.5 -52.5], 'g')
            %xlabel('s', 'FontSize',14)
            %ylabel('mV', 'FontSize',14)
            xlabel('s', 'fontsize',20)
            set(gca, 'FontSize', 20)
            %plot(bd(:,1), zeros(length(bd),1), 'r.')
            
            axis([0 xmax -90 70])
            x = [parameterA num2str(parameter) label];
            text(.25,90, x,'FontSize',20);
            axes('Position', [0.1 0.95 0.1 0.3])
            axis off
            text(5.75,.05,'g_{CaS}1 = 12.3 nS','fontsize', 20)
            print(f,'-depsc',[num2str(run1) 'code2neurons/code2/plots/' num2str(run2) '/' num2str(run4) '.eps'])
            close(f);
end
end
end

